 Здесь весь код ...
 
```c
|-----------------|   |---------------|   |---------------|   |---------------|
| main.cpp        |   | global.h      |<--| mylib.h       |<--| debug.h       |
|-----------------|   |---------------|   |---------------|   |---------------|
        ^                   |  |  |
        |                   v  v  v
|-----------------|     <<========'
| render.h        |
|-----------------|
        ^ 
        '------------. 
                     | 
|-----------------|  | 
| _games    ...   |->|
|-----------------|  |
                     |
                     |
|-----------------|  |
| _gui      ...   |->|
|-----------------|  |
                     |
                     |
|-----------------|  |
| _log      ...   |->|
|-----------------|  |
                     |
                     |
|-----------------|  |
| _redactor ...   |->'
|-----------------|

```

