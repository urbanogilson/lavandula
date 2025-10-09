create table users (
    username text primary key,
    password text not null
);

insert into users(username, password) values ('admin', 'password');