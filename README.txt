How to buid:
~~~~~~~~~~~
	make


How to test:
~~~~~~~~~~~
make test
./compare 5   1 2 5 7 12 14
<  5 : FoundLess    idx=1
<= 5 : FoundExact   idx=2
== 5 : FoundExact   idx=2
>= 5 : FoundExact   idx=2
>  5 : FoundGreater idx=3


Test from commandline:
~~~~~~~~~~~~~~~~~~~~~~
Devas-MacBook-Pro-2:compare dpandian$ ./compare 9   20 17 16 12 8 2 1
<  9 : FoundLess    idx=4
<= 9 : FoundLess    idx=4
== 9 : NotFound     idx=-1
>= 9 : FoundGreater idx=3
>  9 : FoundGreater idx=3

