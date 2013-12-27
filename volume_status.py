"""Simple app to get the current volume and mute status of machine it's run on.
"""
import commands
import re

class Error(Exception):
  """Every error is derived from exception."""

class CommandError(Error):
  """Raised when a system command returns nonzero."""

class VolumeStatus(object):

  def __init__(self, *args, **kargs):
    self.command = "amixer get 'Master'"
    self.amixer_output = self._GetAmixerOutput(self.command)
    self.channel_name_regex_pattern = r"Playback channels: ([\w ]+)"
    self.channel = self._GetPlaybackChanel()
    self.vol_state_regex_pattern = (r"%s: Playback \d?\d?\s?\[(\d+?)%%\]" %
        self.channel)
    self.mute_state_regex_pattern = r"%s: Playback.+?\s\[(\w\w\w?)\]" % self.channel

  def _GetAmixerOutput(self, command):
    """Get output from amixer."""
    status, output = commands.getstatusoutput(self.command)
    if status != 0:
      raise CommandError(("%s [Fail]" % self.command))
    return output

  def _GetPlaybackChanel(self):
    """read Playback Chanel field from output of amixer get 'Master'."""
    channel_match = re.search(self.channel_name_regex_pattern, self.amixer_output)
    if channel_match:
      return channel_match.group(1)
    else:
      return None

  def GetVolumePercent(self):
    """looks for percent value of channel_name playback volume."""
    if not self.channel:
      channel= "Mono"
    vol_match = re.search(self.vol_state_regex_pattern, self.amixer_output)
    if vol_match:
      return int(vol_match.group(1))
    else:
      return -1

  def IsMuted(self):
    """looks for state channel_name playback."""
    state_match = re.search(self.mute_state_regex_pattern, self.amixer_output)
    if state_match:
      return state_match.group(1).lower() == "off".lower()
    return False


def main():
  """Prints volume status of current machime."""
  vol_stat = VolumeStatus()
  output = "%d%%" % (vol_stat.GetVolumePercent())
  if vol_stat.IsMuted():
    output = "%s %s" % (output, 'M')
  print output

if __name__ == '__main__':
  main()
