// #define _XOPEN_SOURCE 700
#include <ftw.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/inotify.h>
#include <vector>
// #include <unordered_map>
#include <unordered_map>

#define MAX_DIRS 4096
// TODO(macpd): correctly retrieve PATH_MAX
/* #define PATH_MAX 256 */
using std::string;
using std::vector;
// using __gnu_cxx::unordered_map;
using std::unordered_map;

std::vector<string> dirs;
static const uint32_t DESIRED_EVENTS_MASK = IN_CREATE | IN_DELETE | IN_DELETE_SELF | IN_MOVE_SELF | IN_MOVE;
int inotify_fd;
// unordered_map<string, int> dirs;
// int cur_dir_idx = 0;

void fullEntityName(const string& base, const char* name, string& result) {
  result.clear();
  result.append(base);
  if (result.size() != 0 && result[result.size() - 1] != '/') {
    result.append("/");
  }
  result.append(name);
}

/* process inotify_event structure
 * prints event and adds/removes dirs when created or destoryed
 * returns true if successful, otherwise false
 */
bool processInotifyEvent(struct inotify_event *i, unordered_map<int, string>& fd_map, unordered_map<uint32_t, string>& cookie_map, unordered_map<string, string>& moved_dir_map) {
    fprintf(stderr, "wd =%2d; ", i->wd);
    if (i->cookie > 0) {
      fprintf(stderr, "cookie =%4d; ", i->cookie);
    }
    if (i->len > 0) {
      fprintf(stderr, "len = %d; name = %s\n", i->len, i->name);
    }

    if(i->mask & IN_IGNORED) {
      fprintf(stderr, "IN_IGNORED\n");
      return true;
    }

    unordered_map<int, string>::iterator iter = fd_map.find(i->wd);
    if (iter == fd_map.end()) {
        fprintf(stderr, "Unable to find fd %2d in watch FD map\n", i->wd);
        return false;
    }
    string event_location = iter->second;
    fprintf(stderr, "Event in %s\n", event_location.c_str());
    string entity_name;
    fullEntityName(event_location, i->name, entity_name);

    if (i->mask & IN_CREATE) {
      fprintf(stderr, "IN_CREATE\n");
      // new directory. print name, and watch.
      if (i->mask & IN_ISDIR) {
        printf("New Directory: %s\n", entity_name.c_str());
        int fd = inotify_add_watch(inotify_fd, entity_name.c_str(), DESIRED_EVENTS_MASK);
        fprintf(stderr, "inotify watch fd for %s: %2d\n", entity_name.c_str(), fd);
        fd_map.insert(std::make_pair(fd, entity_name));
        return true;
      } else {
        printf("New File: %s\n", entity_name.c_str());
        return true;
      }
    }

    if (i->mask & IN_DELETE_SELF) {
      fprintf(stderr, "IN_DELETE_SELF\n");
      if(! i->mask & IN_ISDIR) {
        fprintf(stderr, "Something is wrong. Self delete event is not for a directory (%s), but only directory should be watched.\n", entity_name.c_str());
        return false;
      } else {
        fd_map.erase(i->wd);
        return true;
      }
    }

    if (i->mask & IN_DELETE) {
      fprintf(stderr, "IN_DELETE\n");
      if (i->mask & IN_ISDIR) {
        printf("Directory deleted: %s\n", entity_name.c_str());
        return true;
      } else {
        printf("File deleted: %s\n", entity_name.c_str());
        return true;
      }
    }

    if (i->mask & IN_MOVE_SELF) {
      fprintf(stderr, "IN_MOVE_SELF\n");
      if(! i->mask & IN_ISDIR) {
        fprintf(stderr, "Something is wrong. Self move event is not for a directory (%s), but only directory should be watched.\n", entity_name.c_str());
        return false;
      } else {
        // lookup new name in moved_dir_map and update in fd_map
        unordered_map<string, string>::iterator new_name = moved_dir_map.find(event_location);
        if (new_name == moved_dir_map.end()) {
          fprintf(stderr, "Unable to locate new name for %s\n", event_location.c_str());
          return false;
        }
        fd_map[i->wd] = new_name->second;
        printf("Directory moved from %s to %s\n", event_location.c_str(), new_name->second.c_str());
        return true;
      }
    }

    if (i->mask & IN_MOVED_FROM) {
      fprintf(stderr, "IN_MOVED_FROM\n");
      cookie_map.insert(std::make_pair(i->cookie, entity_name));
      if (i->mask & IN_ISDIR) {
        printf("Directory moved from: %s\n", entity_name.c_str());
        return true;
      } else {
        printf("File moved from: %s\n", entity_name.c_str());
        return true;
      }
    }

    if (i->mask & IN_MOVED_TO) {
      fprintf(stderr, "IN_MOVED_TO\n");
      unordered_map<uint32_t, string>::iterator iter = cookie_map.find(i->cookie);
      string old_name;
      if (iter != cookie_map.end()) {
        old_name = iter->second.c_str();
      }
      if (i->mask & IN_ISDIR) {
        printf("Directory moved from %s to %s\n", old_name.c_str(), entity_name.c_str());
        moved_dir_map.insert(std::make_pair(old_name, entity_name));
        return true;
      } else {
        printf("File moved from %s to: %s\n", old_name.c_str(), entity_name.c_str());
        return true;
      }
    }

    if (i->mask & IN_Q_OVERFLOW) {
      fprintf(stderr, "IN_Q_OVERFLOW\n");
      return false;
    }

    if (i->mask & IN_UNMOUNT) {
      fprintf(stderr, "IN_UNMOUNT\n");
      printf("%s unmounted\n", entity_name.c_str());
      fd_map.erase(i->wd);
      return true;
    }
    printf("\n");
    return false;
}


int nftw_callback(const char* pathname, const struct stat *statbuf, int typeflag, struct FTW *ftwbuf) {
  if (S_ISDIR(statbuf->st_mode)) {
    dirs.push_back(pathname);
    // size_t len = strnlen(pathname, PATH_MAX);
    // dirs[cur_dir_idx], pathname, len);
    // dirs.push_back(string(pathname));
    // if (len == PATH_MAX) {
      // dirs[cur_dir_idx][PATH_MAX] = '\0';
    // }
    // cur_dir_idx++;
   // } else { 
    /* fprintf(stderr, "Skipping non-directory %s\n", pathname); */
  } 
  return 0;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Usage: %s <directory path>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  // ensure directory path exists
  struct stat stat_buf;
  if (stat(argv[1], &stat_buf) == -1) {
    fprintf(stderr, "Unable to stat %s.", argv[1]);
    exit(EXIT_FAILURE);
  } else if (!S_ISDIR(stat_buf.st_mode)) {
    fprintf( stderr, "%s is not a directory.", argv[1]);
    exit(EXIT_FAILURE);
  }

  if (nftw(argv[1], nftw_callback, 100, FTW_MOUNT) != 0) {
    perror("ntfw failed.");
  }

  printf("Dirs found:\n");
  // for (int i = 0; i < cur_dir_idx; i++) {
    // printf("%s\n", dirs[i].first);
  // }
  for (auto iter = dirs.begin(); iter != dirs.end(); iter++) {
    printf("%s\n", (*iter).c_str());
  }

  inotify_fd = inotify_init();
  if (inotify_fd == -1) {
    perror("ionotify_init");
  }

  unordered_map<int, string> watch_fd_pathname_map;
  for (vector<string>::iterator iter = dirs.begin(); iter != dirs.end(); iter++) {
    const int& watch_fd = inotify_add_watch(inotify_fd, (*iter).c_str(), DESIRED_EVENTS_MASK);
    watch_fd_pathname_map.insert(std::make_pair(watch_fd, *iter));
  }
  for (unordered_map<int, string>::iterator iter = watch_fd_pathname_map.begin(); iter != watch_fd_pathname_map.end(); iter++) {
    fprintf(stderr, "Watch fd: %d -> %s\n", iter->first, iter->second.c_str());
  }

  ssize_t bytes_read;
  long name_max = pathconf(argv[1], _PC_NAME_MAX);
  fprintf(stderr, "pathconf(argv[1], _PC_NAME_MAX): %ld\n", name_max);
  struct inotify_event* event;
  char* event_buf_cursor;
  char event_buf[10 * (sizeof(struct inotify_event) + name_max + 1)];
  // map of cookie to previous filename
  unordered_map<uint32_t, string> cookie_map;
  unordered_map<string, string> moved_dir_map;

  while ((bytes_read = read(inotify_fd, event_buf, sizeof(event_buf))) != 0) {
    if (bytes_read == -1) {
      perror("Error reading inotify instance.");
      exit(EXIT_FAILURE);
    }
    for (event_buf_cursor = event_buf; event_buf_cursor < event_buf + bytes_read; /* event_buf_cursor incremented in loop */) {
      event = (struct inotify_event*) event_buf_cursor;
      processInotifyEvent(event, watch_fd_pathname_map, cookie_map, moved_dir_map);
      event_buf_cursor += sizeof(struct inotify_event) + event->len;
    }
  }

  exit(EXIT_SUCCESS);
}
