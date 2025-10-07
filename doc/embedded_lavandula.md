# Embedded Lavandula (ELA)

Lavandula provides HTML templating in the form of Embedded Lavandula (ELA), a templating language.

Here is an example.

```c
// someFile.c

char *greeting = "Welcome to Lavandula!"
```

```html
// someOtherFile.html.ela

<p> {{ greeting }} <p>
```

Generates the following output

```
Welcome To Lavandula!
```