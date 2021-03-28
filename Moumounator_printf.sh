dir=$(pwd)
echo $dir
echo "${basedir}"

if [[ "$OSTYPE" == "linux-gnu" ]]; then
        COLOR_FLAG=\\e
        ECHO_FLAG=-ne
elif [[ "$OSTYPE" == "darwin"* ]]; then
        COLOR_FLAG=\\x1B
        ECHO_FLAG=
fi
clear
echo "${COLOR_FLAG}[38;5;220m"
cat cat/cat.txt
echo
echo
echo ${ECHO_FLAG} "\t\t\t" | tr -d '\n' ; for i in {16..22} {21..16} {15..22} {21..16} ; do echo ${ECHO_FLAG} "${COLOR_FLAG}[38;5;${i}m₪${COLOR_FLAG}[0m" | tr -d '\n'; done ; echo
echo ${ECHO_FLAG} "\t\t\t" | tr -d '\n'; for i in {16..22} {21..21} ; do echo ${ECHO_FLAG} "${COLOR_FLAG}[38;5;${i}m₪${COLOR_FLAG}[0m" | tr -d '\n'; done ; echo ${ECHO_FLAG} "Moumounator" | tr -d '\n';
for i in {21..21} {22..16} ; do echo ${ECHO_FLAG} "${COLOR_FLAG}[38;5;${i}m₪${COLOR_FLAG}[0m" | tr -d '\n'; done ; echo
echo ${ECHO_FLAG} "\t\t\t" | tr -d '\n'; for i in {16..22} {21..20} ; do echo ${ECHO_FLAG} "${COLOR_FLAG}[38;5;${i}m₪${COLOR_FLAG}[0m" | tr -d '\n'; done ; echo ${ECHO_FLAG} "FT_PRINTF" | tr -d '\n';
for i in {20..21} {22..16} ; do echo ${ECHO_FLAG} "${COLOR_FLAG}[38;5;${i}m₪${COLOR_FLAG}[0m" | tr -d '\n'; done ; echo
echo ${ECHO_FLAG} "\t\t\t" | tr -d '\n'; for i in {16..22} {21..16} {15..22} {21..16} ; do echo ${ECHO_FLAG} "${COLOR_FLAG}[38;5;${i}m₪${COLOR_FLAG}[0m" | tr -d '\n'; done ; echo
echo
echo ${ECHO_FLAG} "${COLOR_FLAG}[1m"
sleep 1
if [ $# = 0 ]
then
  echo ${ECHO_FLAG} "Need path file."
  echo ${ECHO_FLAG} "Correct use:"
  echo ${ECHO_FLAG} "./Moumounator_printf.sh <../path_to_your_printf> (cspduixX%) (012)"
  echo
  exit
fi
touch output_printf.txt
touch output_user.txt
cd $1 2> /dev/null
if [ $? = 1 ]
then
  echo ${ECHO_FLAG} "Incorrect path file"
  echo ${ECHO_FLAG} "Correct use:"
  echo ${ECHO_FLAG} "./Moumounator_printf.sh <../path_to_your_printf> (cspduixX%) (012)"
  echo
  exit
fi
make >> /dev/null
if [ $? = 2 ]
then
  echo ${ECHO_FLAG} "Make does not compile"
  echo
  exit
fi

mv *.a "$dir/" && cd "$dir/"
if [ "$2" = "-bonus" ]
then
  COMPIL=bonus
  shift
else
  COMPIL=all
fi

if [ "$2" = "-new" ]
then
  : > save.bonus
fi

gcc -I$1/includes/ -I$1 -I$1/srcs/ -g -Wall -Wextra -Werror main_${COMPIL}.c gnl/*.c -L. -lftprintf -fsanitize=address && ./a.out $2 $3
retvalue=$?
if [ "$retvalue" = "1" ]
then
  echo ${ECHO_FLAG} "\n\t\t${COLOR_FLAG}[1m${COLOR_FLAG}[31m---------------"
  echo ${ECHO_FLAG} "\t\t|ERROR COMPILE|"
  echo ${ECHO_FLAG} "\t\t${COLOR_FLAG}[1m${COLOR_FLAG}[31m---------------${COLOR_FLAG}[0m"
  echo ${ECHO_FLAG} "${COLOR_FLAG}[1m"
  echo ${ECHO_FLAG} "Trying new compile command"
  echo
  echo ${ECHO_FLAG} "Removing -fsanitize=adress"
  echo ${ECHO_FLAG} "gcc main_all.c gnl/*.c -L. -lftprintf && ./a.out $2 $3"
  gcc -I$1/includes/ -I$1 -I$1/srcs/ -Wall -Wextra -Werror main_${COMPIL}.c gnl/*.c -L. -lftprintf && ./a.out $2 $3
fi
if [ $? = 1 ]
then
  echo ${ECHO_FLAG} "\n\t\t${COLOR_FLAG}[1m${COLOR_FLAG}[31m---------------"
  echo ${ECHO_FLAG} "\t\t|ERROR COMPILE|"
  echo ${ECHO_FLAG} "\t\t${COLOR_FLAG}[1m${COLOR_FLAG}[31m---------------${COLOR_FLAG}[0m"
  echo ${ECHO_FLAG} "${COLOR_FLAG}[1m"
  echo
  echo ${ECHO_FLAG} "Did you do anything wrong?"
  echo ${ECHO_FLAG} "Refer to README:"
  echo ${ECHO_FLAG} "${COLOR_FLAG}[1m"
  cat README
fi
echo ${ECHO_FLAG} "${COLOR_FLAG}[38;5;220m"
cat cat/error.txt
echo
echo ${ECHO_FLAG} "${COLOR_FLAG}[0;1m"
echo ${ECHO_FLAG} "         Thanks for using Moumounator (Meow)"
rm -rf *.a a.out output_printf.txt output_user.txt a.out.*