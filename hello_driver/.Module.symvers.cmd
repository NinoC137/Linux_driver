cmd_/home/ninobox/linux_driver/hello_driver/Module.symvers := sed 's/\.ko$$/\.o/' /home/ninobox/linux_driver/hello_driver/modules.order | scripts/mod/modpost -m -a  -o /home/ninobox/linux_driver/hello_driver/Module.symvers -e -i Module.symvers   -T -
