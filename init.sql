create table todos (
    id integer primary key autoincrement,
    title text not null,
    completed boolean not null default 0
);

insert into todos (title, completed) values ('Learn C', 1);
insert into todos (title, completed) values ('Build a web app', 0);
insert into todos (title, completed) values ('Profit', 0);