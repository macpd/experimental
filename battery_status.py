#! /usr/bin/python
# reads the state of the AC adapter from acpi infromation in /sys/class/power_supply
# prints on-line if connected, off-line elsewise

import re
import sys
import os
#import argparse


class BatteryStatus:

  def __init__(self):
    self.verbose_mode = False
    self.ac_state_filename = "/sys/class/power_supply/AC/online"
    self.bat_info_dir = "/sys/class/power_supply/BAT0/"

  # finds file full capacity filename (with optional prefix in dir), returns None if not found
  def GetFullCapacatiyFileName(self,dirname,prefix=None):
    if self.verbose_mode:
      print "Searching %s for full capacity, with prefix %s" % (dirname,prefix)
    # directory sanity check
    if not os.path.exists(dirname):
      sys.strerr.write("%s not found" % dirname)
      sys.exit(1)
    prefix_list = list()
    dir_contents = os.listdir(dirname)
    if prefix is not None:
      prefix_list.append(prefix)
    else:
      prefix_list = ['energy','charge']
    for filename in dir_contents:
      #if filename.lower().startswith(prefix) or (filename.lower().startswith("energy") or filename.lower().startswith("charge")):
      for p in prefix_list:
        if filename.lower().startswith(p) and filename.endswith("full"):
          if self.verbose_mode:
            print "Found match: %s" % filename
          return os.path.join(dirname,filename)
    # if no match found return none
    if self.verbose_mode:
      print "No match found"
    return None

  def GetCurCapacityFileName(self,dirname,prefix=None):
    if self.verbose_mode:
      print "Searching %s for full capacity, with prefix %s" % (dirname,prefix)
    if not os.path.exists(dirname):
      sys.strerr.write("%s not found" % dirname)
      sys.exit(1)
    dir_contents = os.listdir(dirname)
    prefix_list = list()
    if prefix is not None:
      prefix_list.append(prefix)
    else:
      prefix_list = ['energy','charge']
    dir_contents = os.listdir(dirname)
    for filename in dir_contents:
      #if filename.lower().startswith(prefix) or (filename.lower().startswith("energy") or filename.lower().startswith("charge")):
      for p in prefix_list:
        if filename.lower().startswith(p) and filename.lower().endswith("now"):
          if self.verbose_mode:
            print "Found match: %s" % filename
          return os.path.join(dirname,filename)
    # if no match found return none
    if self.verbose_mode:
      print "No match found"
    return None

  # read state of AC power from specified file (hopefully in /sys)
  def IsOnACPower(self,filename):
    if self.verbose_mode:
      print "Searching %s for state of AC power" % filename
    state_file = open(filename,'r')
    state_raw_info = state_file.read()
    state_file.close()
    if self.verbose_mode:
      print "%s: %s" % (filename,state_raw_info)
    if state_raw_info.find("1") != -1 :
      #print "+"
      return True
    else:
      #print "?"
      return False

  # read max battery capcity from specified file
  def GetMaxBatteryCapacity(self,filename):
    info_file = open(filename,'r')
    info_text = info_file.read()
    info_file.close()
    max_capacity = float(info_text)
    if self.verbose_mode:
      print "%s: %s" % (filename,max_capacity)
    if max_capacity is not None and max_capacity != 0:
      return max_capacity
    else:
      sys.stderr.write("[Error] battery max capacity not found!")

  # read current battery capacity from specified file
  def GetCurrentBatteryCapacity(self,filename):
    state_file = open(filename,'r')
    state_text = state_file.read()
    state_file.close()
    curr_capacity = float(state_text)
    if self.verbose_mode:
      print "%s: %s" % (filename,curr_capacity)
    if curr_capacity is not None and curr_capacity != 0:
      return curr_capacity
    else:
      sys.stderr.write("[Error] battery max capacity not found!")

  # returns battery percent
  def ChargePercent(self,prefix=None,percision=1):
    self.bat_full_filename = self.GetFullCapacatiyFileName(self.bat_info_dir,prefix)
    if prefix is None:
      prefix = os.path.basename(self.bat_full_filename)
      underbar_index = prefix.find("_")
      if underbar_index != -1:
        prefix = prefix[:underbar_index]
    if self.verbose_mode:
      print "prefix: %s" % prefix
    bat_curr_filename = self.GetCurCapacityFileName(self.bat_info_dir,prefix)
    if self.bat_full_filename is None or bat_curr_filename is None:
      sys.stderr.write("Full battery capacity information not found in %s" % self.bat_info_dir)
      sys.exit(1)
    max_cap = self.GetMaxBatteryCapacity(self.bat_full_filename)
    curr_cap = self.GetCurrentBatteryCapacity(bat_curr_filename)
    curr_percent = (curr_cap/max_cap) * 100
    if self.verbose_mode:
      print "Capacity: %f" % curr_percent
    return "%.*f" % (percision,curr_percent)

  def ACConnectionSymbol(self):
    if self.IsOnACPower(self.ac_state_filename):
      return "+"
    else:
      return "-"

def main():
  # parse agrs
  #parser = argparse.ArgumentParser(description="Read battery information from %s (atempting to find correct files), print percent remaining and whether charging (+) or dishcharging(-)" % (bat_info_dir))
  #parser.add_argument('-v','--verbose',action='store_true',default=False,help="verbose mode")
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
