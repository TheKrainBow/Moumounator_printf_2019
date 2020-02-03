echo
echo -en "\t" ; for i in {16..22} {21..16} {15..22} {21..16} ; do echo -en "\e[38;5;${i}m₪\e[0m" ; done ; echo
echo -en "\t" ; for i in {16..22} {21..21} ; do echo -en "\e[38;5;${i}m₪\e[0m" ; done ; echo -en "Moumounator" ;
for i in {21..21} {22..16} ; do echo -en "\e[38;5;${i}m₪\e[0m" ; done ; echo
echo -en "\t" ; for i in {16..22} {21..20} ; do echo -en "\e[38;5;${i}m₪\e[0m" ; done ; echo -en "FT_PRINTF" ;
for i in {20..21} {22..16} ; do echo -en "\e[38;5;${i}m₪\e[0m" ; done ; echo
echo -en "\t" ; for i in {16..22} {21..16} {15..22} {21..16} ; do echo -en "\e[38;5;${i}m₪\e[0m" ; done ; echo

cd your_printf >> /dev/null && make >> /dev/null && mv libftprintf.a .. && cd .. && gcc -w main_all.c gnl/*.c -L. -lftprintf && ./a.out $1 $2
if [ $? = 1 ]
then
  echo -e "\n\t\t\e[1m\e[31m---------------"
  echo -e "\t\t|ERROR COMPILE|"
  echo -e "\t\t\e[1m\e[31m---------------\e[0m"
  echo "Trying new compile command"
  echo
  echo "cd your_printf >> /dev/null && make >> /dev/null && mv *.a .. && cd .. && gcc -w main_all.c gnl/*.c *.a >> /dev/null && ./a.out $1 $2"
  cd your_printf >> /dev/null && make >> /dev/null && mv *.a .. && cd .. && gcc -w main_all.c gnl/*.c *.a >> /dev/null && ./a.out $1 $2
fi
if [ $? = 1 ]
then
  echo -e "\n\t\t\e[1m\e[31m---------------"
  echo -e "\t\t|ERROR COMPILE|"
  echo -e "\t\t\e[1m\e[31m---------------\e[0m"
  echo
  echo "Did you do anything wrong?"
  echo "Refer to README:"
  echo -e "\e[1m"
  cat README
fi