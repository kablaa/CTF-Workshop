```
struct auth { //note the lack of typedef
  char name[32];
  int auth;
};

struct auth *auth; // naming the struct pointer the same as the struct its self
char *service;
```




Let's look at the auth function
```    
if(strncmp(line, "auth ", 5) == 0)
{
    auth = malloc(sizeof(auth)); // should be sizeof(struct auth)
    memset(auth, 0, sizeof(auth));

    if(strlen(line + 5) < 31)
        strcpy(auth->name, line + 5);
}
```

Let's take this line by line and look at the corresponding assembly

```
auth = malloc(sizeof(auth)); // should be sizeof(struct auth)
```

```
804866e:	83 ec 0c             	sub    esp,0xc
8048671:	6a 04                	push   0x4
8048673:	e8 08 fe ff ff       	call   8048480 <malloc@plt>
8048678:	83 c4 10             	add    esp,0x10
804867b:	a3 e8 9a 04 08       	mov    ds:0x8049ae8,eax
```
This is the main bug in this program. Because the dev wrote `sizeof(auth)` and not `sizeof(struct auth)`, there will be `0x4` bytes of memory (the size of \*`auth`) allocated and not `0x24` (the size of `struct auth`).




Lets see what happens with the service case
```
if(strncmp(line, "service", 6) == 0)
    service = strdup(line + 7); //this will stored on the heap
```
notice that we do not have any restrictions

```
80486fc:	6a 06                	push   0x6
80486fe:	68 59 88 04 08       	push   0x8048859
8048703:	8d 85 78 ff ff ff    	lea    eax,[ebp-0x88]
8048709:	50                   	push   eax
804870a:	e8 e1 fd ff ff       	call   80484f0 <strncmp@plt>
804870f:	83 c4 10             	add    esp,0x10
8048712:	85 c0                	test   eax,eax
8048714:	75 1a                	jne    8048730 <main+0x135>
8048716:	8d 85 78 ff ff ff    	lea    eax,[ebp-0x88]
804871c:	83 c0 07             	add    eax,0x7
804871f:	83 ec 0c             	sub    esp,0xc
8048722:	50                   	push   eax
8048723:	e8 28 fd ff ff       	call   8048450 <strdup@plt>
8048728:	83 c4 10             	add    esp,0x10
804872b:	a3 ec 9a 04 08       	mov    ds:0x8049aec,eax
```


Let's take a look at the login command

```    
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

```
if(auth->auth)
```

```
8048751:	a1 e8 9a 04 08       	mov    eax,ds:0x8049ae8
8048756:	8b 40 20             	mov    eax,DWORD PTR [eax+0x20] ;0x20 offset
8048759:	85 c0                	test   eax,eax
804875b:	74 25                	je     8048782 <main+0x187>
```
