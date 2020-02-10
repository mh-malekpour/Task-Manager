# Task Manager

Input/Output example:
```
~ add
~ title is Do homework
~ starts in 02-01 15:05
~ ends in 02-01 15:55
~ done
~ today
>    (1) “Do homework” [15:05 - 15:55]
~ add
~ title is Read book
~ starts in 02-01 15:45
~ ends in 02-01 21:30
~ done
~ today
>    (1) “Do homework” [15:05 - 15:55]
>    (2) “Read book” [15:45 - 21:30]
~ schedule 02-01
>    (1) “Do homework” [15:05 - 15:55]
~ free 02-01 21:01
~ today
>    (1) “Do homework” [15:05 - 15:55]
~ now
>    02-01 14:35
~ find time 1:00
>    02-01 [15:55 - 16:55]
```
