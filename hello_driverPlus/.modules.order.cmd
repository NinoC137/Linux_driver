cmd_/home/ninobox/linux_driver/hello_driverPlus/modules.order := {   echo /home/ninobox/linux_driver/hello_driverPlus/hello_driverPlus.ko; :; } | awk '!x[$$0]++' - > /home/ninobox/linux_driver/hello_driverPlus/modules.order
