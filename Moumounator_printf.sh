dir=$(pwd)
echo $dir
echo "${basedir}"

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
echo
if [ $# = 0 ]
then
  echo "Need path file."
  echo "Correct use:"
  echo "./Moumounator_printf.sh <../path_to_your_printf> (cspduixX%) (012)"
  echo
  exit
fi
cd $1 2> /dev/null
if [ $? = 1 ]
then
  echo "Incorrect path file"
  echo "Correct use:"
  echo "./Moumounator_printf.sh <../path_to_your_printf> (cspduixX%) (012)"
  echo
  exit
fi
make >> /dev/null
if [ $? = 2 ]
then
  echo "Make does not compile"
  echo
  exit
fi

mv *.a "$dir/" && cd "$dir/" && gcc -w main_all.c gnl/*.c -L. -lftprintf && ./a.out $2 $3
if [ $? = 1 ]
then
  echo "\n\t\t${COLOR_FLAG}[1m${COLOR_FLAG}[31m---------------"
  echo "\t\t|ERROR COMPILE|"
  echo "\t\t${COLOR_FLAG}[1m${COLOR_FLAG}[31m---------------${COLOR_FLAG}[0m"
  echo "Trying new compile command"
  echo
  echo "cd your_printf >> /dev/null && make >> /dev/null && mv *.a .. && cd .. && gcc -w main_all.c gnl/*.c *.a >> /dev/null && ./a.out $1 $2"
  gcc -w main_all.c gnl/*.c *.a >> /dev/null && ./a.out $1 $2
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