## Named pipes

```
mkfifo myfifo
gcc reader.c -o reader
gcc writer.c -o writer
./reader
./writer
```
