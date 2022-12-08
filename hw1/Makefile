#잘 이해 했습니다.
diary_exe : memo.o calendar.o main.o  #memo.o,calender.o,main.o로 diary_exe생성
	gcc -o diary_exe memo.o calendar.o main.o

memo.o : memo.c			#memo.c를 depenency로 memo.o 생성
	gcc -c -o memo.o memo.c
calendar.o : calendar.c		#calendar.c를 dependency로 calendar.o 생성
	gcc -c -o calendar.o calendar.c
main.o : main.c			#main.c를 dependency로 main.o 생성
	gcc -c -o main.o main.c
clean :				#만든 실행파일과 *.o 삭제
	rm *.o diary_exe
