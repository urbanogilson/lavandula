# CORS Policy Configuration

Lavandula provides an API to configure the CORS policy for your web application.

An example CORS policy configuration can be seen below.

```c
CorsConfig policy = corsPolicy();

// only allow requests from this origin
allowOrigin(&policy, "www.example.com");

// only allow the requests to be of these HTTP actions
allowMethod(&policy, HTTP_GET);
allowMethod(&policy, HTTP_POST);

// apply the policy to the application builder
useCorsPolicy(&builder, policy);
```

To allow any origin to access your application, use the following method.

```c
allowAnyOrigin(&policy);
```

To allow any method in your application, use the following method.

```c
allowAnyMethod(&policy);
```

If you would like to allow any method and any origin, then you can eliminate the above with this one-liner.

```c
useCorsPolicy(&builder, corsAllowAll());
```
