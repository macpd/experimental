#! /usr/bin/python
# reads the state of the AC adapter from acpi infromation in /sys/class/power_supply
# prints on-line if connected, off-line elsewise

import re
import sys
import os
#import argparse


class Error(Exception):
  pass

class DirectoryNotFoundError(Error):
  """Raised when a specified directory doesn't exist or is unreadable."""
  pass

class BatteryStatus:

  def __init__(self):
    self.verbose_mode = False
    self.ac_state_file_name = "/sys/class/power_supply/AC/online"
    self.bat_info_dir = "/sys/class/power_supply/BAT0/"

  def FileNamesWithPatternInDir(self, dirname, prefixes=[], suffixes=[]):
    """Returns a list of all files that start with prefix and end with suffix."""
    if self.verbose_mode:
      print "Looking in %s for files starting with %r and ending with %r" % (dirname, prefixes, suffixes)

    # directory sanity check
    if not os.path.exists(dirname):
      sys.stderr.write("%s not found" % dirname)
      raise DirectoryNotFoundError

    dir_contents = os.listdir(dirname)
    matches = []
    for file_name in dir_contents:
      for p in prefixes:
        if file_name.lower().startswith(p):
          if suffixes:
            for s in suffixes:
              if file_name.lower().endswith(s):
                matches.append(os.path.join(dirname, file_name))
          else:
            matches.append(os.path.join(dirname, file_name))

    if self.verbose_mode:
      print "Found match: %s" % file_name
    return matches


  def GetFullCapacatiyFileName(self, dirname, prefixes):
    """Finds file full capacity file_name (with optional prefix in dir), returns None if not found."""
    if not prefixes:
      prefixes = ['energy','charge']
    if self.verbose_mode:
      print "Searching %s for full capacity, with prefix %s" % (dirname, prefixes)
    full_capacity_file_name = self.FileNamesWithPatternInDir(dirname, prefixes, suffixes=['full'])
    if not full_capacity_file_name and self.verbose_mode:
      print "No match found"
    return full_capacity_file_name[0]

  def GetCurCapacityFileName(self, dirname, prefixes=['energy','charge']):
    """Finds file current capacity file_name (with optional prefix in dir), returns None if not found."""
    cur_capacity_file_name = self.FileNamesWithPatternInDir(dirname, prefixes=prefixes, suffixes=['now'])
    if not cur_capacity_file_name and self.verbose_mode:
      print "No match found"
    return cur_capacity_file_name[0]

  def IsOnACPower(self, file_name):
    """Reads state of AC power from specified file (hopefully in /sys)."""
    if self.verbose_mode:
      print "Searching %s for state of AC power" % file_name
    state_file = open(file_name,'r')
    state_raw_info = state_file.read()
    state_file.close()
    if self.verbose_mode:
      print "%s: %s" % (file_name, state_raw_info)

    return state_raw_info.find("1") != -1

  def GetMaxBatteryCapacity(self, file_name):
    """Reads max battery capcity from specified file."""
    info_file = open(file_name,'r')
    info_text = info_file.read()
    info_file.close()
    max_capacity = float(info_text)
    if self.verbose_mode:
      print "%s: %s" % (file_name, max_capacity)
    if max_capacity is not None and max_capacity != 0:
      return max_capacity
    else:
      sys.stderr.write("[Error] battery max capacity not found!")

  def GetCurrentBatteryCapacity(self, file_name):
    """Reads current battery capacity from specified file."""
    state_file = open(file_name,'r')
    state_text = state_file.read()
    state_file.close()
    curr_capacity = float(state_text)
    if self.verbose_mode:
      print "%s: %s" % (file_name, curr_capacity)
    if curr_capacity is not None and curr_capacity != 0:
      return curr_capacity
    else:
      sys.stderr.write("[Error] battery current capacity not found!")

  def ChargePercent(self, prefix=None, percision=1):
    """Gets percent charge and appends an optional prefix."""
    self.bat_full_file_name = self.GetFullCapacatiyFileName(self.bat_info_dir, prefix)
    if prefix is None:
      prefix = os.path.basename(self.bat_full_file_name)
      underbar_index = prefix.find("_")
      if underbar_index != -1:
        prefix = prefix[:underbar_index]
    if self.verbose_mode:
      print "prefix: %s" % prefix
    bat_curr_file_name = self.GetCurCapacityFileName(self.bat_info_dir, prefix)
    if self.bat_full_file_name is None or bat_curr_file_name is None:
      sys.stderr.write("Full battery capacity information not found in %s" % self.bat_info_dir)
      sys.exit(1)
    max_cap = self.GetMaxBatteryCapacity(self.bat_full_file_name)
    curr_cap = self.GetCurrentBatteryCapacity(bat_curr_file_name)
    curr_percent = (curr_cap/max_cap) * 100
    if self.verbose_mode:
      print "Capacity: %f" % curr_percent
    return "%.*f" % (percision, curr_percent)

  def ACConnectionSymbol(self):
    if self.IsOnACPower(self.ac_state_file_name):
      return "+"
    else:
      return "-"

def main():
  # parse agrs
  #parser = argparse.ArgumentParser(description="Read battery information from %s (atempting to find correct files), print percent remaining and whether charging (+) or dishcharging(-)" % (bat_info_dir))
  #parser.add_argument('-v','--verbose',action='store_true',default=False, help="verbose mode")
  #TODO provide arg to read from a porvided directory
  #parser.add_argument('--dir',dest='alt_dir',nargs=1,metavar="DIR",help="alternate directory to serach for battery information files")
  #args = parser.parse_args()
  #if verbose:
  #  print "verbosity time"
  args = sys.argv[1:]
  bat = BatteryStatus()
  if "--verbose" in args:
    bat.verbose_mode = True
  else:
    bat.verbose_mode= False

  print "%s %s" % (bat.ChargePercent(), bat.ACConnectionSymbol())

  sys.exit(0)

if __name__ == "__main__":
  main()
