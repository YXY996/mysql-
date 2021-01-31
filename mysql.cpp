mysql
--如何在数据库服务器中创建我们的数据库
create database test;
use test

--如何创建一个数据表
create table pet(
name varchar(20),
owner varchar(20),
species varchar(20),
sex char(1),
birth date,
death date
);
--查看数据表结构
mysql-describe pet;
--如何查看数据表 中的记录
mysql> select *from pet;
Empty set (0.01 sec)
--如何往数据表中添加数据记录
insert into pet values('pul','Die','hamer','f','1990-3-3',NULL);

INSERT INTO pet VALUES ('puffball', 'Diane', 'hamster', 'f', '1990-03-30', NULL);
inser into pet values('旺财','周星驰','dog','公','1996-3-1',NULL);
--mysql 常用数据类型有哪些
mysql 支持多种类型，可以分为三类
create table testType
(
	number TINYINT
	);

INSERT INTO testType VALUES(127);
select * from testType;
+--------+
| number |
+--------+
|    127 |
+--------+
1 row in set (0.00 sec)

--数据记录常见操作
--增加
INSERT
--删除
Delete
--修改
update
--查询
select
mysql建表约束 .sql
--主键约束
他能够唯一确定一张表中的一条记录，也就是我们通过给某个字段添加约束，使得该字段不重复且不为空
create table user(
	id int primary key,
	name varchar(20)
	);
INSERT INTO user VALUES(1,'张三');
INSERT INTO user VALUES(2,'李四');
//注意一定要注意逗号等符号的格式，中英文切换容易造成格式错误
--联合主键
--只要联合的主键值加起来不重复就可以 //完全重复不可以
create table user2(
id int,
name varchar(20),
password varchar(20),
primary key (id,name)
);
insert into user2 values(1,'张三','123');
insert into user2 values(2,'张三','123');
insert into user2 values(1,'李四','123');
insert into user2 values(NULL,'李四','123');
//并且主键值都不能为空
--自增约束
insert into user5 values(1,'张三');
 
create table user6(
	id int,
	name varchar(20),
	unique (name));
create table user7(
	id int,
	name varchar(20)unique);
create table user8(
	id int,
	name varchar(20),
	unique (id,name));
mysql> desc user8;
+-------+-------------+------+-----+---------+-------+
| Field | Type        | Null | Key | Default | Extra |
+-------+-------------+------+-----+---------+-------+
| id    | int         | YES  | MUL | NULL    |       |
| name  | varchar(20) | YES  |     | NULL    |       |
+-------+-------------+------+-----+---------+-------+

insert into user8 values(1,'张三');
insert into user8 values(1,'张三');
如何删除唯一约束
--mysql> alter table user7 drop index name;
Query OK, 0 rows affected (0.00 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> desc user7;
+-------+-------------+------+-----+---------+-------+
| Field | Type        | Null | Key | Default | Extra |
+-------+-------------+------+-----+---------+-------+
| id    | int         | YES  |     | NULL    |       |
| name  | varchar(20) | YES  |     | NULL    |       |
+-------+-------------+------+-----+---------+-------+
--modify添加
alter table user7 modify name varchar(20) unique;
--非空约束
--修饰字段不能为空NULL
create table user9(
	id int,
	name varchar(20) not NULL);
INSERT INTO user9(id)values(1);

--mysql> INSERT INTO user9(id)values(1);
ERROR 1364 (HY000): Field 'name' doesn't have a default VALUE
INSERT INTO user9(name)values('zhang');
INSERT INTO user9 values(1,'zhang');
//设定name为非空值，则不能为空，id可为空
mysql> select * from user9;
+------+-------+
| id   | name  |
+------+-------+
| NULL | zhang |
|    1 | zhang |
+------+-------+
2 rows in set (0.00 sec)

--默认约束
--就是当我们插入字段值时，如果没有传值就会使用默认值
create table user10(
id int,
name varchar(20),
age int default 10);
mysql> desc user10;
+-------+-------------+------+-----+---------+-------+
| Field | Type        | Null | Key | Default | Extra |
+-------+-------------+------+-----+---------+-------+
| id    | int         | YES  |     | NULL    |       |
| name  | varchar(20) | YES  |     | NULL    |       |
| age   | int         | YES  |     | 10      |       |
+-------+-------------+------+-----+---------+-------+
3 rows in set (0.00 sec)

