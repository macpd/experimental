#! /usr/bin/python2
"""Prints simple state of the battery charge percent and AC adapter connection.

  Only tested on lenovo laptops.

  This scripts is intended to be flexible to lenovo's firmware which names
  files energy_* when booted from battery, and charge_* when booted with AC
  power connected.
"""

import argparse
import os
import sys


class Error(Exception):
  """Base Error Class."""

class DirectoryNotFoundError(Error):
  """Raised when a specified directory doesn't exist or is unreadable."""

class BatteryStatus:
  """Class to read and parse battery charge infomation."""

  DEFAULT_POWER_STATE_DIR = '/sys/class/power_supply/'
  DEFAULT_AC_STATE_FILE = 'AC/online'
  DEFAULT_BATTERY_STATE_DIR = 'BAT0/'
  DEFAULT_BATTERY_PREFIXES = set(('energy', 'charge'))
  DEFAULT_CURRENT_STATE_SUFFIX = 'now'
  DEFAULT_FULL_STATE_SUFFIX = 'full'

  def __init__(self,
               power_state_dir=None,
               ac_state_fname=None,
               battery_state_dir=None,
               battery_state_prefixes=None,
               current_state_suffix=None,
               full_state_suffix=None,
               verbose=False):
    """Initializes Battery Status object.

      Args:
        power_state_dir: optional dir to search AC and battery information files.
        ac_state_fname: optional filename to parse for AC power status information, is appended to self.power_state_dir
        battery_state_dir: optional dir to search for battery status information files, is appended to self.power_state_dir
        battery_state_prefixes: List of prefixes to identify battery status files.
        verbose: Boolean, whether to print verbose output.
    """
    self.verbose_mode = verbose
    self.power_state_dir = power_state_dir or self.DEFAULT_POWER_STATE_DIR
    self.ac_state_fname = os.path.join(self.power_state_dir,
        (ac_state_fname or self.DEFAULT_AC_STATE_FILE))
    self.battery_state_dir = os.path.join(self.power_state_dir,
        (battery_state_dir or self.DEFAULT_BATTERY_STATE_DIR))
    self.battery_prefixes = battery_state_prefixes or self.DEFAULT_BATTERY_PREFIXES
    self.cur_state_suffix = current_state_suffix or self.DEFAULT_CURRENT_STATE_SUFFIX
    self.full_state_suffix = full_state_suffix or self.DEFAULT_FULL_STATE_SUFFIX
    if self.verbose_mode:
      print 'Versbose mode.'
      print 'Power state dir: %s' % self.power_state_dir
      print 'AC state file: %s' % self.ac_state_fname
      print 'Battery state dir: %s' % self.battery_state_dir
      print 'Batter state file prefixes: %s' % self.battery_prefixes
      print 'Current state suffix: %s' % self.cur_state_suffix
      print 'Full state suffix: %s' % self.full_state_suffix

  def FileNamesWithPatternInDir(self, dirname, prefixes=None, suffixes=None):
    """Lists all files starting with prefix and ending suffix in the given dir."""
    if self.verbose_mode:
      print 'Looking in %s for files starting with %r and ending with %r' % (dirname, prefixes, suffixes)

    # directory sanity check
    if not os.path.exists(dirname):
      raise DirectoryNotFoundError(dirname)

    prefixes = prefixes or []
    suffixes = suffixes or []

    if isinstance(prefixes, str):
      prefixes = [prefixes]

    if isinstance(suffixes, str):
      suffixes = [suffixes]

    dir_contents = os.listdir(dirname)
    matches = []
    for fname in dir_contents:
      fname_lower = fname.lower()
      for p in prefixes:
        if fname_lower.startswith(p):
          if suffixes:
            for s in suffixes:
              if fname_lower.endswith(s):
                matches.append(os.path.join(dirname, fname))
          else:
            matches.append(os.path.join(dirname, fname))

    if self.verbose_mode:
      print 'Found matches: %r' % matches
    return matches


  def GetFullCapacatiyFileName(self):
    """Finds file full capacity filename, returns None if not found."""
    full_capacity_fname = self.FileNamesWithPatternInDir(self.battery_state_dir, self.battery_prefixes, suffixes=self.full_state_suffix)
    if full_capacity_fname:
      if self.verbose_mode:
        print 'Full capacity filename: %s' % full_capacity_fname
      return full_capacity_fname[0]
    else:
      if self.verbose_mode:
        print 'No match found'


  def GetCurCapacityFileName(self):
    """Finds current capacity filename, returns None if not found."""
    cur_capacity_fname = self.FileNamesWithPatternInDir(self.battery_state_dir, prefixes=self.battery_prefixes, suffixes=self.cur_state_suffix)
    if not cur_capacity_fname:
      if  self.verbose_mode:
        print 'No match found'
      return None
    return cur_capacity_fname[0]

  def IsOnACPower(self):
    """Reads state of AC power connection."""
    if self.verbose_mode:
      print 'Searching %s for state of AC power' % self.ac_state_fname
    state_fname = open(self.ac_state_fname,'r')
    state_raw_info = state_fname.read()
    state_fname.close()
    if self.verbose_mode:
      print '%s: %s' % (self.ac_state_fname, state_raw_info)

    return state_raw_info.find('1') != -1

  def FullBatteryCapacity(self, fname):
    """Reads max battery capcity."""
    info_fname = open(fname,'r')
    info_text = info_fname.read()
    info_fname.close()
    max_capacity = float(info_text)
    if self.verbose_mode:
      print '%s: %s' % (fname, max_capacity)
    if max_capacity:
      return max_capacity
    else:
      sys.stderr.write('[Error] battery max capacity not found!')

  def CurrentBatteryCapacity(self, fname):
    """Reads current battery capacity."""
    state_fname = open(fname,'r')
    state_text = state_fname.read()
    state_fname.close()
    curr_capacity = float(state_text)
    if self.verbose_mode:
      print '%s: %s' % (fname, curr_capacity)
    if curr_capacity:
      return curr_capacity
    else:
      sys.stderr.write('[Error] battery current capacity not found!')

  def ChargePercent(self, percision=1):
    """Calculates percent charge."""
    battery_full_charge_fname = self.GetFullCapacatiyFileName()
    battery_curr_charge_fname = self.GetCurCapacityFileName()
    if not (battery_full_charge_fname and battery_curr_charge_fname):
      sys.stderr.write('Battery capacity information not found in %s' % self.battery_state_dir)
      sys.exit(1)
    full_cap = self.FullBatteryCapacity(battery_full_charge_fname)
    curr_cap = self.CurrentBatteryCapacity(battery_curr_charge_fname)
    curr_percent = (curr_cap/full_cap) * 100
    if self.verbose_mode:
      print 'Capacity: %f' % curr_percent
    return '%.*f' % (percision, curr_percent)

  def ACConnectionSymbol(self):
    return '+' if self.IsOnACPower() else '-'

def main():
  """Parses args, creates battery status object, and prints charge info."""
  parser = argparse.ArgumentParser(
  description=('Read battery information from %s (atempting to find correct '
               'files), print percent remaining and whether charging (+) or '
               'dishcharging(-)') % (BatteryStatus.DEFAULT_BATTERY_STATE_DIR))
  parser.add_argument('-v','--verbose', action='store_true', default=False,
      help='verbose mode')
  parser.add_argument('-d', '--base_dir', dest='power_dir',  metavar='DIR',
      help='Alternative directory to find power information files.')
  parser.add_argument('-b', '--battery', dest='battery', metavar='BATTERY',
      help='Battery to display charge of. ie \'BAT0\'.')
  parser.add_argument('-a', '--ac_state_file', dest='ac_state_fname',
      metavar='FILE', help=('File to get AC state. Unless a full path, will be '
        'assumed relative to BASE_DIR.'))
  #TODO provide args for battery state prefixes, and suffixes
  parser.add_argument('-p', '--prefix', dest='prefix', metavar='PREFIX(ES)',
      action='append', help=('battery status filename prefix. Thinkpads are '
      'notorious for flip flopping between \'energy\' and \'charge\'.'))
  parser.add_argument('-n', '--now_suffix', dest='now_suffix', metavar='SUFFIX',
      help='Current battery filename siffix. default: \'now\'')
  parser.add_argument('-f', '--full_suffix', dest='full_suffix',
      metavar='SUFFIX', help='Full battery filename siffix. default: \'full\'')
  parser.add_argument('-s', '--no_ac_status', dest='show_ac_status',
      action='store_false', default=True, help=('Dont print the +/- indicating '
      'AC connection status'))

  args = parser.parse_args()
  if args.battery and not args.battery.startswith('BAT'):
    args.battery = 'BAT%s' % args.battery

  bat = BatteryStatus(power_state_dir=args.power_dir,
      ac_state_fname=args.ac_state_fname,
      battery_state_dir=args.battery,
      verbose=args.verbose,
      battery_state_prefixes=args.prefix,
      current_state_suffix=args.now_suffix,
      full_state_suffix=args.full_suffix)

  try:
    output = bat.ChargePercent()
    if args.show_ac_status:
      output = '%s %s' % (output, bat.ACConnectionSymbol())
    print output
  except DirectoryNotFoundError as e:
    sys.stderr.write('Unable to find a default or specified directory: %s\n' % e)
    sys.exit(-1)

  sys.exit(0)

if __name__ == '__main__':
  main()
