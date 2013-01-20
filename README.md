experimental
============

playground repo for miscellaneous code and projects


Current Contents
----------------

+ *volume_status.py* A simple pyhton script that prints the volume of alsa's master channel with a 'M' if muted.


+ *battery_status.py* Python script that battery and AC adapter info in a very naive way. Outputs battery percent and +/- to indicate charging/discharging respectively.  Alternate power info dir, ac state file, or battery can be specified via flags

        usage: battery_status.py [-h] [-v] [-d DIR] [-b BATTERY] [-a FILE]

        Read battery information from BAT0/ (atempting to find correct files), print
        percent remaining and whether charging (+) or dishcharging(-)

        optional arguments:
          -h, --help            show this help message and exit
          -v, --verbose         verbose mode
          -d DIR, --base_dir DIR
                                Alternative directory to find power information files.
          -b BATTERY, --battery BATTERY
                                Battery to display charge of. ie 'BAT0'.
          -a FILE, --ac_state_file FILE
                                File to get AC state. Unless a full path, will be
                                assumed relative to BASE_DIR.
