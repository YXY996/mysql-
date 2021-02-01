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
--or表示或者
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
--7 以class降序查询student表的所有记录
--升序 降序
desc 降序
asc  升序 （不写也默认升序）
mysql> select *from student order by class desc;
+-----+-----------+-----+------------+-------+
| no  | name      | sex | birthday   | class |
+-----+-----------+-----+------------+-------+
| 101 | 曾华      | 男  | 1977-09-01 | 95033 |
| 103 | 王丽      | 女  | 1976-01-23 | 95033 |
| 104 | 李军      | 男  | 1976-02-20 | 95033 |
| 107 | 王尼玛    | 男  | 1976-02-20 | 95033 |
| 102 | 匡明      | 男  | 1975-10-02 | 95031 |
| 105 | 王芳      | 女  | 1975-02-10 | 95031 |
| 106 | 陆军      | 男  | 1974-06-03 | 95031 |
| 108 | 张全蛋    | 男  | 1975-02-10 | 95031 |
| 109 | 赵铁柱    | 男  | 1974-06-03 | 95031 |
+-----+-----------+-----+------------+-------+
==8.以cno升序，degree降序查询score表的记录

mysql> select * from score order by c_no asc, degree desc;
//课程编号首先按照升序排列，同一课程编号内的score按照降序排列
+------+-------+--------+
| s_no | c_no  | degree |
+------+-------+--------+
| 103  | 3-105 |     92 |
| 105  | 3-105 |     88 |
| 109  | 3-105 |     76 |
| 103  | 3-245 |     86 |
| 105  | 3-245 |     75 |
| 109  | 3-245 |     68 |
| 103  | 6-166 |     85 |
| 109  | 6-166 |     81 |
| 105  | 6-166 |     79 |
+------+-------+--------+
--9.查询‘95301’班级的人数
--统计count

mysql> select count(*)from student where class='95031';
+----------+
| count(*) |
+----------+
|        5 |
+----------+

--10 查询score表中的最高分的学生学号和课程号

--mysql> select s_no,c_no from score where degree=(select max(degree) from score);
//按照括号内首先找出表中的最高分 select  max(degree) from score;
然后来查询最高分的学生学号和课程号 select s_no,c_no score where degree =select  max(degree) from score;

+------+-------+
| s_no | c_no  |
+------+-------+
| 103  | 3-105 |
+------+-------+
--第二种做法：排序
首先将分数按升序或者降序排序，然后找出排在首位或者末尾的数据

mysql> select s_no,c_no,degree from score order by degree;
+------+-------+--------+
| s_no | c_no  | degree |
+------+-------+--------+
| 109  | 3-245 |     68 |
| 105  | 3-245 |     75 |
| 109  | 3-105 |     76 |
| 105  | 6-166 |     79 |
| 109  | 6-166 |     81 |
| 103  | 6-166 |     85 |
| 103  | 3-245 |     86 |
| 105  | 3-105 |     88 |
| 103  | 3-105 |     92 |
然后找出排在首位或者末尾的数据
这里是通过desc找到从最后开始倒数的第一个数据
limit 
第一个数字表示从哪个位置开始
第二个数字代表插入几组数据
limit 0,1
mysql> select s_no,c_no,degree from score order by degree desc limit 0,1;
+------+-------+--------+
| s_no | c_no  | degree |
+------+-------+--------+
| 103  | 3-105 |     92 |
+------+-------+--------+

--11.查询每门课的平均成绩
//查询有几门课程
select * from course;
--avg
select avg(degree) from score where c_no='3-105';
mysql> select avg(degree) from score where c_no='3-105';

+-------------+
| avg(degree) |
+-------------+
|     85.3333 |
+-------------+

select avg(degree) from score where c_no='3-245';
select avg(degree) from score where c_no='6-166';
select avg(degree) from score where c_no='9-888';

--能不能在一个sql语句中写呢？
select c_no,avg(degree) from score group by c_no;

mysql> select c_no,avg(degree) from score group by c_no;
+-------+-------------+
| c_no  | avg(degree) |
+-------+-------------+
| 3-105 |     85.3333 |
| 3-245 |     76.3333 |
| 6-166 |     81.6667 |
+-------+-------------+
//这里尝试不通过课程编号进行分组，通过学生编号进行分组，这里求出的数值代表每名学生所有成绩的平均值.
//因此这个语句主要取决于group by的后半部分
mysql> select s_no,avg(degree) from score group by s_no;

+------+-------------+
| s_no | avg(degree) |
+------+-------------+
| 103  |     87.6667 |
| 105  |     80.6667 |
| 109  |     75.0000 |

--12 查询score表中至少有两名学生选修的，并以3开头的课程的平均分数
3%模糊查询 
select c_no ,avg(degree),count(*)from score group by c_no
having count(c_no)>=2 
and c_no like '3%';

mysql> select c_no ,avg(degree),count(*)from score group by c_no
    -> having count(c_no)>=2 and c_no like '3%';
+-------+-------------+----------+
| c_no  | avg(degree) | count(*) |
+-------+-------------+----------+
| 3-105 |     85.3333 |        3 |
| 3-245 |     76.3333 |        3 |
--13 查询分数大于70 小于90的 s_no 列
 
 select s_no,degree from score where degree>70 and degree<90;
 select s_no,degree from score where degree between 70 and 90;


 mysql> select s_no,degree from score where degree>70 and degree<90;
+------+--------+
| s_no | degree |
+------+--------+
| 103  |     86 |
| 103  |     85 |
| 105  |     88 |
| 105  |     75 |
| 105  |     79 |
| 109  |     76 |
| 109  |     81 |
+------+--------+
--14 查询所有学生的sname 
select no,name from student;
+-----+-----------+
| no  | name      |
+-----+-----------+
| 101 | 曾华      |
| 102 | 匡明      |
| 103 | 王丽      |
| 104 | 李军      |
| 105 | 王芳      |
| 106 | 陆军      |
| 107 | 王尼玛    |
| 108 | 张全蛋    |
| 109 | 赵铁柱    |

select s_no,c_no ,degree from score;

| s_no | c_no  | degree |
+------+-------+--------+
| 103  | 3-105 |     92 |
| 103  | 3-245 |     86 |
| 103  | 6-166 |     85 |
| 105  | 3-105 |     88 |
| 105  | 3-245 |     75 |
| 105  | 6-166 |     79 |
| 109  | 3-105 |     76 |
| 109  | 3-245 |     68 |
| 109  | 6-166 |     81 |
+------+-------+--------+


select name,no,degree from student,score where student.no=score.s_no;
+-----------+-----+--------+
| name      | no  | degree |
+-----------+-----+--------+
| 王丽      | 103 |     92 |
| 王丽      | 103 |     86 |
| 王丽      | 103 |     85 |
| 王芳      | 105 |     88 |
| 王芳      | 105 |     75 |
| 王芳      | 105 |     79 |
| 赵铁柱    | 109 |     76 |
| 赵铁柱    | 109 |     68 |
| 赵铁柱    | 109 |     81 |
+-----------+-----+--------+
--15 查询所有学生的s_no,cname,和degree列
首先分别查看score，course表格

mysql> select c_no,s_no,degree from score;
+-------+------+--------+
| c_no  | s_no | degree |
+-------+------+--------+
| 3-105 | 103  |     92 |
| 3-245 | 103  |     86 |
| 6-166 | 103  |     85 |
| 3-105 | 105  |     88 |
| 3-245 | 105  |     75 |
| 6-166 | 105  |     79 |
| 3-105 | 109  |     76 |
| 3-245 | 109  |     68 |
| 6-166 | 109  |     81 |
+-------+------+--------+

mysql> select no,name from course;
+-------+-----------------+
| no    | name            |
+-------+-----------------+
| 3-105 | 计算机导论      |
| 3-245 | 操作系统        |
| 6-166 | 数字电路        |
| 9-888 | 高等数学        |

+-------+-----------------+
制定新的表格包含no，name（来自course）和degree(score)
增加条件（course里的课程编号与score里的c_no 相等）

mysql> select no,name,degree from course,score where course.no=score.c_no;
+-------+-----------------+--------+
| no    | name            | degree |
+-------+-----------------+--------+
| 3-105 | 计算机导论      |     92 |
| 3-105 | 计算机导论      |     88 |
| 3-105 | 计算机导论      |     76 |
| 3-245 | 操作系统        |     86 |
| 3-245 | 操作系统        |     75 |
| 3-245 | 操作系统        |     68 |
| 6-166 | 数字电路        |     85 |
| 6-166 | 数字电路        |     79 |
| 6-166 | 数字电路        |     81 |
+-------+-----------------+--------+
--16 查询所有学生的sname，cname和degree

mysql> select name,name,degree from student,course,score where student.no=score.s_no and where course.no=score.c_no;
ERROR 1064 (42000): You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near 'where course.no=score.c_no' at line 1

!!我这里尝试按照视频中操作，但因为course和student里的name相同起了冲突
这里按照之前操作数据表的方法 将student中的name改为sname！！
mysql> alter table student drop name;
Query OK, 0 rows affected (0.01 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> alter table student add sname varchar(20) first;
Query OK, 0 rows affected (0.01 sec)
Records: 0  Duplicates: 0  Warnings: 0
desc查看 发现更改成功！
mysql> desc student;
+----------+-------------+------+-----+---------+-------+
| Field    | Type        | Null | Key | Default | Extra |
+----------+-------------+------+-----+---------+-------+
| sname    | varchar(20) | YES  |     | NULL    |       |
| no       | varchar(20) | NO   | PRI | NULL    |       |
| sex      | varchar(10) | NO   |     | NULL    |       |
| birthday | date        | YES  |     | NULL    |       |
| class    | varchar(20) | YES  |     | NULL    |       |
+----------+-------------+------+-----+---------+-------+

select sname,name,degree from student,course,score where student.no=score.s_no and where course.no=score.c_no;
这里再次尝试操作发现还是错误 检查得知虽然数据表中name改为sname
但是sname中的数据为NULL空 所以需要通过对于数据进行操作 

+-----+-----------+
| no  | name      |
+-----+-----------+
| 101 | 曾华      |
| 102 | 匡明      |
| 103 | 王丽      |
| 104 | 李军      |
| 105 | 王芳      |
| 106 | 陆军      |
| 107 | 王尼玛    |
| 108 | 张全蛋    |
| 109 | 赵铁柱    |
--更改数据
UPDATE student SET sname = '曾华 ' where no = 101;
UPDATE student SET sname = '匡明' where no = 102;
UPDATE student SET sname = '王丽' where no = 103;
UPDATE student SET sname = '李军' where no = 104;
UPDATE student SET sname = '王芳' where no = 105;
UPDATE student SET sname = '陆军' where no = 106;
UPDATE student SET sname = '王尼玛' where no = 107;
UPDATE student SET sname = '张全蛋' where no = 108;
UPDATE student SET sname = '赵铁柱' where no = 109;


mysql> select * from student;
+-------+-----+-----+------------+-------+
| sname | no  | sex | birthday   | class |
+-------+-----+-----+------------+-------+
| NULL  | 101 | 男  | 1977-09-01 | 95033 |
| NULL  | 102 | 男  | 1975-10-02 | 95031 |
| NULL  | 103 | 女  | 1976-01-23 | 95033 |
| NULL  | 104 | 男  | 1976-02-20 | 95033 |
| NULL  | 105 | 女  | 1975-02-10 | 95031 |
| NULL  | 106 | 男  | 1974-06-03 | 95031 |
| NULL  | 107 | 男  | 1976-02-20 | 95033 |
| NULL  | 108 | 男  | 1975-02-10 | 95031 |
| NULL  | 109 | 男  | 1974-06-03 | 95031 |
+-------+-----+-----+------------+-------+

select sname,name,degree from student,course,score where student.no=score.s_no and course.no=score.c_no;
成功！

mysql> select sname,name,degree from student,course,score where student.no=score.s_no and course.no=score.c_no;
+-----------+-----------------+--------+
| sname     | name            | degree |
+-----------+-----------------+--------+
| 王丽      | 计算机导论      |     92 |
| 王丽      | 操作系统        |     86 |
| 王丽      | 数字电路        |     85 |
| 王芳      | 计算机导论      |     88 |
| 王芳      | 操作系统        |     75 |
| 王芳      | 数字电路        |     79 |
| 赵铁柱    | 计算机导论      |     76 |
| 赵铁柱    | 操作系统        |     68 |
| 赵铁柱    | 数字电路        |     81 |
+-----------+-----------------+--------+
!!重点 数据操作指令多加练习
前面更改数据表列名的方法很麻烦
查找后发现可以直接修改列名的方法
alter table student change sname name varchar(20);
change oldname newname +数据类型
