# Authentication in Lavandula

There are multiple ways you can perform authenticate within your web application. An array of authentication methods are supported and built-in to the framework to make development easier.


## Basic Authentication

The simplest form of authentication you can add into your application is HTTP Basic Authentication.

```c
// .

useMiddleware(&builder, basicAuth);

// ..
```