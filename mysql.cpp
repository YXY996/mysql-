mysql
登陆mysql
mysql -uroot-p输入密码
--显示数据库
show databases;

--如何在数据库服务器中创建我们的数据库
create database test;
--切换数据库
use test
--显示数据库中所有的表
show tables;
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
省略写成 desc pet
--如何查看数据表 中的记录
mysql> select *from pet;
Empty set (0.01 sec)
--如何往数据表中添加数据记录
insert into pet values('pul','Die','hamer','f','1990-3-3',NULL);
//大小写均可以
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
INSERT INTO pet VALUES ('puffball', 'Diane', 'hamster', 'f', '1990-03-30', NULL);
--删除
Delete
删除数据
DELETE FROM pet where name = 'squirrel';
删除表
delete table pet;
--修改
update
UPDATE pet SET name = 'squirrel' where owner = 'Diane';
--查询
select
SELECT * from pet;

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
--只要联合的主键值加起来不重复就可以 //完全重复不可以.其中至少有一个不相同可以
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
-- 添加主键约束
-- 如果忘记设置主键，还可以通过SQL语句设置（两种方式）：
ALTER TABLE user ADD PRIMARY KEY(id);//选择数据表，然后添加数据类型为主键约束
ALTER TABLE user MODIFY id INT PRIMARY KEY;//将数据表中的某一个数据修改为主键约束
--自增约束
--自增约束的主键由系统自动递增分配
create table user(
	id int primary key auto_increment,
	name varchar(20));
--唯一约束
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
insert into user10 (id,name)values(1,'zhangsan');
//age 未赋值 所以age显示默认值
mysql> select * from user10;
+------+----------+------+
| id   | name     | age  |
+------+----------+------+
|    1 | zhangsan |   10 |
+------+----------+------+
1 row in set (0.00 sec)
--外键约束
--涉及到两个表 父表子表
--主表 副表
--班级
create table classes(
id int primary key,
name varchar(20)
);

--学生表
create table students(
id int primary key,
name varchar(20),
class_id int,
foreign key (class_id) references classes (id)
);



insert into classes values(1,'一班');
insert into classes values(2,'二班');
insert into classes values(3,'三班');
insert into classes values(4,'四班');


mysql> select * from classes;
+----+--------+
| id | name   |
+----+--------+
|  1 | 一班   |
|  2 | 二班   |
|  3 | 三班   |
|  4 | 四班   |
+----+--------+
4 rows in set (0.00 sec)
--删除主表中的数据

mysql> delete from classes where id=4;
Query OK, 1 row affected (0.01 sec)

mysql> select * from classes;
+----+--------+
| id | name   |
+----+--------+
|  1 | 一班   |
|  2 | 二班   |
|  3 | 三班   |
+----+--------+
3 rows in set (0.00 sec)

insert into students values(1001,'zhangsan',1);
insert into students values(1002,'zhangsan',2);
insert into students values(1003,'zhangsan',3);
//因为刚才通过delete和删除了四班 所以只输入前三组数据
insert into students values(1004,'zhangsan',4);
//查看结果没有问题 classses父表中的班级数据被子表引用
mysql> select * from students;
+------+----------+----------+
| id   | name     | class_id |
+------+----------+----------+
| 1001 | zhangsan |        1 |
| 1002 | zhangsan |        2 |
| 1003 | zhangsan |        3 |
+------+----------+----------+
3 rows in set (0.00 sec)
再次尝试删除主表数据

mysql> delete from classes where id=3;
ERROR 1451 (23000): Cannot delete or update a parent row: a foreign key constraint fails (`test`.`students`, CONSTRAINT `students_ibfk_1` FOREIGN KEY (`class_id`) REFERENCES `classes` (`id`))
得到的结果是erro 说明当主表的记录被副表引用后，是不可以被删除的。但是被引用前可以随意删除
 --数据库的三大设计范式.sql
  --1
  INF 
  --数据表中的 所有字段都是不可分割的原子值
  create table student2(
  id int primary key,
  name varchar(20),
  address varchar(30)
  );

  insert into student2 values(1,'zhangsan','武侯区武侯大道100号');
  insert into student2 values(2,'lisi','武侯区京城大道200号');
  insert into student2 values(3,'wang5','高新区王府大道300号');
mysql> select * from student2;
+----+----------+-----------------------------+
| id | name     | address                     |
+----+----------+-----------------------------+
|  1 | zhangsan | 武侯区武侯大道100号         |
|  2 | lisi     | 武侯区京城大道200号         |
|  3 | wang5    | 高新区王府大道300号         |
+----+----------+-----------------------------+
3 rows in set (0.00 sec)

--字段值还可以继续拆分的就不满足第一范式
 create table student3(
 id int primary key,
 name varchar(20),
 district varchar(30),
 number varchar(30));


先创建了一个数据表，之后发现数据表中数据不完善，需要再添加一个变量的时候，这里使用alter命令。
mysql> alter table student3 add details varchar(30);
Query OK, 0 rows affected (0.01 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> desc student3;
+----------+-------------+------+-----+---------+-------+
| Field    | Type        | Null | Key | Default | Extra |
+----------+-------------+------+-----+---------+-------+
| id       | int         | NO   | PRI | NULL    |       |
| name     | varchar(20) | YES  |     | NULL    |       |
| district | varchar(30) | YES  |     | NULL    |       |
| number   | varchar(30) | YES  |     | NULL    |       |
| details  | varchar(30) | YES  |     | NULL    |       |
+----------+-------------+------+-----+---------+-------+
//添加
mysql> alter table student3 add details varchar(30);
//指定某一个位置添加新变量
mysql> alter table student3 add details varchar(30) after district;

//删除
mysql> alter table student3 drop details varchar(30);

insert into student3 values(1,'zhangsan','武侯区','武侯大道','100号');
insert into student3 values(2,'lisi','武侯区','京城大道','200号');
insert into student3 values(3,'wang5','高新区','王府大道','300号');


mysql> select *from student3;
+----+----------+-----------+--------------+--------+
| id | name     | district  | details      | number |
+----+----------+-----------+--------------+--------+
|  1 | zhangsan | 武侯区    | 武侯大道     | 100号  |
|  2 | lisi     | 武侯区    | 京城大道     | 200号  |
|  3 | wang5    | 高新区    | 王府大道     | 300号  |
+----+----------+-----------+--------------+--------+
3 rows in set (0.00 sec)

--范式设计的越详细，对于某些实际操作可能更好，但不一定都是好的
--2.第二范式
--必须满足第一范式的前提下，第二范式要求，除主键外的每一列都必须完全依赖于主键
--如果要出现不完全依赖，只可能发生在联合逐渐的情况下
--订单表
create table myorder(
product_id int,
customer_id int,
product_name varchar(20),
customer_name varchar(20),
primary key(product_id,customer_id)
);
--除主键以外的其他列，只依赖于主键的部分字段
--拆表
create table myorder(
order_id int primary key,
product_id int,
customer_id);
create table product(
id int primary key,
name varchar(20));
create table customer(
id int primary key,
name varchar(20));
--分成三个表之后，就满足了第二范式的设计！
--3.第三范式
--3NF
--必须先满足第二范式，除开主键列的其他列之间不能有传递依赖关系

create table myorder(
	order_id int primary key,
	product_id int,
	customer_id int，
	//customer_phone varchar(20)
);
create table customer(create table customer(
id int primary key,
name varchar(20));
	id int primary key,
	name varchar(20)
	phone varchar(20)
	);
customer_phone 和 customer_id可能存在联系，和除主键外的其他列存在联系不符合第三范式
所以在这里将phone这一列放到table customer中

查询边学边练
-- 创建数据库
CREATE DATABASE select_test;
-- 切换数据库
USE select_test;

-- 创建学生表
CREATE TABLE student (
    no VARCHAR(20) PRIMARY KEY,
    name VARCHAR(20) NOT NULL,
    sex VARCHAR(10) NOT NULL,
    birthday DATE, -- 生日
    class VARCHAR(20) -- 所在班级
);

-- 创建教师表
CREATE TABLE teacher (
    no VARCHAR(20) PRIMARY KEY,
    name VARCHAR(20) NOT NULL,
    sex VARCHAR(10) NOT NULL,
    birthday DATE,
    profession VARCHAR(20) NOT NULL, -- 职称
    department VARCHAR(20) NOT NULL -- 部门
);

-- 创建课程表
CREATE TABLE course (
    no VARCHAR(20) PRIMARY KEY,
    name VARCHAR(20) NOT NULL,
    t_no VARCHAR(20) NOT NULL, -- 教师编号
    -- 表示该 tno 来自于 teacher 表中的 no 字段值
    FOREIGN KEY(t_no) REFERENCES teacher(no) 
);

-- 成绩表
CREATE TABLE score (
    s_no VARCHAR(20) NOT NULL, -- 学生编号
    c_no VARCHAR(20) NOT NULL, -- 课程号
    degree DECIMAL,	-- 成绩
    -- 表示该 s_no, c_no 分别来自于 student, course 表中的 no 字段值
    FOREIGN KEY(s_no) REFERENCES student(no),	
    FOREIGN KEY(c_no) REFERENCES course(no),
    -- 设置 s_no, c_no 为联合主键
    PRIMARY KEY(s_no, c_no)
);

-- 查看所有表
SHOW TABLES;
mysql> show tables;
+-----------------------+
| Tables_in_select_test |
+-----------------------+
| course                |
| score                 |
| student               |
| teacher               |
+-----------------------+
4 rows in set (0.00 sec)


-- 添加学生表数据
INSERT INTO student VALUES('101', '曾华', '男', '1977-09-01', '95033');
INSERT INTO student VALUES('102', '匡明', '男', '1975-10-02', '95031');
INSERT INTO student VALUES('103', '王丽', '女', '1976-01-23', '95033');
INSERT INTO student VALUES('104', '李军', '男', '1976-02-20', '95033');
INSERT INTO student VALUES('105', '王芳', '女', '1975-02-10', '95031');
INSERT INTO student VALUES('106', '陆军', '男', '1974-06-03', '95031');
INSERT INTO student VALUES('107', '王尼玛', '男', '1976-02-20', '95033');
INSERT INTO student VALUES('108', '张全蛋', '男', '1975-02-10', '95031');
INSERT INTO student VALUES('109', '赵铁柱', '男', '1974-06-03', '95031');

-- 添加教师表数据
INSERT INTO teacher VALUES('804', '李诚', '男', '1958-12-02', '副教授', '计算机系');
INSERT INTO teacher VALUES('856', '张旭', '男', '1969-03-12', '讲师', '电子工程系');
INSERT INTO teacher VALUES('825', '王萍', '女', '1972-05-05', '助教', '计算机系');
INSERT INTO teacher VALUES('831', '刘冰', '女', '1977-08-14', '助教', '电子工程系');

-- 添加课程表数据
INSERT INTO course VALUES('3-105', '计算机导论', '825');
INSERT INTO course VALUES('3-245', '操作系统', '804');
INSERT INTO course VALUES('6-166', '数字电路', '856');
INSERT INTO course VALUES('9-888', '高等数学', '831');

-- 添加添加成绩表数据
INSERT INTO score VALUES('103', '3-105', '92');
INSERT INTO score VALUES('103', '3-245', '86');
INSERT INTO score VALUES('103', '6-166', '85');
INSERT INTO score VALUES('105', '3-105', '88');
INSERT INTO score VALUES('105', '3-245', '75');
INSERT INTO score VALUES('105', '6-166', '79');
INSERT INTO score VALUES('109', '3-105', '76');
INSERT INTO score VALUES('109', '3-245', '68');
INSERT INTO score VALUES('109', '6-166', '81');

--1.查询student表中的所有数据
mysql> select * from student;
+-----+-----------+-----+------------+-------+
| no  | name      | sex | birthday   | class |
+-----+-----------+-----+------------+-------+
| 101 | 曾华      | 男  | 1977-09-01 | 95033 |
| 102 | 匡明      | 男  | 1975-10-02 | 95031 |
| 103 | 王丽      | 女  | 1976-01-23 | 95033 |
| 104 | 李军      | 男  | 1976-02-20 | 95033 |
| 105 | 王芳      | 女  | 1975-02-10 | 95031 |
| 106 | 陆军      | 男  | 1974-06-03 | 95031 |
| 107 | 王尼玛    | 男  | 1976-02-20 | 95033 |
| 108 | 张全蛋    | 男  | 1975-02-10 | 95031 |
| 109 | 赵铁柱    | 男  | 1974-06-03 | 95031 |
+-----+-----------+-----+------------+-------+
9 rows in set (0.00 sec)

--2.查询student表中的所有记录的sname，ssex和class列
mysql> select name,sex,class from student;
+-----------+-----+-------+
| name      | sex | class |
+-----------+-----+-------+
| 曾华      | 男  | 95033 |
| 匡明      | 男  | 95031 |
| 王丽      | 女  | 95033 |
| 李军      | 男  | 95033 |
| 王芳      | 女  | 95031 |
| 陆军      | 男  | 95031 |
| 王尼玛    | 男  | 95033 |
| 张全蛋    | 男  | 95031 |
| 赵铁柱    | 男  | 95031 |
+-----------+-----+-------+
9 rows in set (0.00 sec)

--3.查询教师所有的单位，不重复的department
//直接查询会有重复部分
mysql> select department from teacher;
+-----------------+
| department      |
+-----------------+
| 计算机系        |
| 计算机系        |
| 电子工程系      |
| 电子工程系      |
+-----------------+
4 rows in set (0.00 sec)

//这里使用distinct语句来排除重复
mysql> select distinct department from teacher;
+-----------------+
| department      |
+-----------------+
| 计算机系        |
| 电子工程系      |
+-----------------+
2 rows in set (0.00 sec)
--4 查询score表中成绩在60-80之间的所有记录
--查询区间between ...and ..
mysql> select * from score where degree between 60 and 80;
+------+-------+--------+
| s_no | c_no  | degree |
+------+-------+--------+
| 105  | 3-245 |     75 |
| 105  | 6-166 |     79 |
| 109  | 3-105 |     76 |
| 109  | 3-245 |     68 |
+------+-------+--------+
--直接使用运算符比较
mysql> select * from score where degree>60 and degree<80;
+------+-------+--------+
| s_no | c_no  | degree |
+------+-------+--------+
| 105  | 3-245 |     75 |
| 105  | 6-166 |     79 |
| 109  | 3-105 |     76 |
| 109  | 3-245 |     68 |
+------+-------+--------+
--5.查询score表中成绩为85，86或88的记录
mysql> select * from score where degree in(85,86,88);
+------+-------+--------+
| s_no | c_no  | degree |
+------+-------+--------+
| 103  | 3-245 |     86 |
| 103  | 6-166 |     85 |
| 105  | 3-105 |     88 |
+------+-------+--------+

--6  查询student表中“95301班”或性别为“女”的记录
mysql> select * from student where class='95301' or'sex='女';
    '> select * from student where class='95031' or'sex='女';
ERROR 1064 (42000): You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near '女'
//上述问题也是由于单引号位置问题，仔细检查即可，有错误的时候看erro提示
mysql> select * from student where class='95031' or sex='女';
+-----+-----------+-----+------------+-------+
| no  | name      | sex | birthday   | class |
+-----+-----------+-----+------------+-------+
| 102 | 匡明      | 男  | 1975-10-02 | 95031 |
| 103 | 王丽      | 女  | 1976-01-23 | 95033 |
| 105 | 王芳      | 女  | 1975-02-10 | 95031 |
| 106 | 陆军      | 男  | 1974-06-03 | 95031 |
| 108 | 张全蛋    | 男  | 1975-02-10 | 95031 |
| 109 | 赵铁柱    | 男  | 1974-06-03 | 95031 |
+-----+-----------+-----+------------+-------+


