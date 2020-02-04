if [[ "$OSTYPE" == "linux-gnu" ]]; then
        COLOR_FLAG=\\e
        ECHO_FLAG=${ECHO_FLAG}
elif [[ "$OSTYPE" == "darwin"* ]]; then
        COLOR_FLAG=\\x1B
        ECHO_FLAG=
fi

echo
echo ${ECHO_FLAG} "\t" | tr -d '\n' ; for i in {16..22} {21..16} {15..22} {21..16} ; do echo ${ECHO_FLAG} "${COLOR_FLAG}[38;5;${i}m₪${COLOR_FLAG}[0m" | tr -d '\n'; done ; echo
echo ${ECHO_FLAG} "\t" | tr -d '\n'; for i in {16..22} {21..21} ; do echo ${ECHO_FLAG} "${COLOR_FLAG}[38;5;${i}m₪${COLOR_FLAG}[0m" | tr -d '\n'; done ; echo ${ECHO_FLAG} "Moumounator" | tr -d '\n';
for i in {21..21} {22..16} ; do echo ${ECHO_FLAG} "${COLOR_FLAG}[38;5;${i}m₪${COLOR_FLAG}[0m" | tr -d '\n'; done ; echo
echo ${ECHO_FLAG} "\t" | tr -d '\n'; for i in {16..22} {21..20} ; do echo ${ECHO_FLAG} "${COLOR_FLAG}[38;5;${i}m₪${COLOR_FLAG}[0m" | tr -d '\n'; done ; echo ${ECHO_FLAG} "FT_PRINTF" | tr -d '\n';
for i in {20..21} {22..16} ; do echo ${ECHO_FLAG} "${COLOR_FLAG}[38;5;${i}m₪${COLOR_FLAG}[0m" | tr -d '\n'; done ; echo
echo ${ECHO_FLAG} "\t" | tr -d '\n'; for i in {16..22} {21..16} {15..22} {21..16} ; do echo ${ECHO_FLAG} "${COLOR_FLAG}[38;5;${i}m₪${COLOR_FLAG}[0m" | tr -d '\n'; done ; echo

cd your_printf >> /dev/null && make >> /dev/null && mv libftprintf.a .. && cd .. && gcc -w main_all.c gnl/*.c -L. -lftprintf && ./a.out $1 $2
if [ $? = 1 ]
then
  echo -e "\n\t\t${COLOR_FLAG}[1m${COLOR_FLAG}[31m---------------"
  echo -e "\t\t|ERROR COMPILE|"
  echo -e "\t\t${COLOR_FLAG}[1m${COLOR_FLAG}[31m---------------${COLOR_FLAG}[0m"
  echo "Trying new compile command"
  echo
  echo "cd your_printf >> /dev/null && make >> /dev/null && mv *.a .. && cd .. && gcc -w main_all.c gnl/*.c *.a >> /dev/null && ./a.out $1 $2"
  cd your_printf >> /dev/null && make >> /dev/null && mv *.a .. && cd .. && gcc -w main_all.c gnl/*.c *.a >> /dev/null && ./a.out $1 $2
fi
if [ $? = 1 ]
then
  echo -e "\n\t\t${COLOR_FLAG}[1m${COLOR_FLAG}[31m---------------"
  echo -e "\t\t|ERROR COMPILE|"
  echo -e "\t\t${COLOR_FLAG}[1m${COLOR_FLAG}[31m---------------${COLOR_FLAG}[0m"
  echo
  echo "Did you do anything wrong?"
  echo "Refer to README:"
  echo -e "${COLOR_FLAG}[1m"
  cat README
fi