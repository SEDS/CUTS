--
-- @file        CUTS-unittest.sql
--
-- $Id$
--
-- @author      Hamilton Turner
--

-- ============================================================================
-- BEGIN TABLES
-- ============================================================================

-- main table for log formats
-- contains all one-one info
-- eventually this should be a PCRE regex so its universal
-- Also, we should eventually make the regex case sensitive
CREATE TABLE IF NOT EXISTS  cuts.log_formats (
  lfid            INT             NOT NULL auto_increment,
  lfmt            VARCHAR(150)    NOT NULL,
  icase_regex     VARCHAR(180)    NOT NULL,
  csharp_regex    VARCHAR(200)    DEFAULT NULL,

  -- set the constraints for the table
  PRIMARY KEY  (lfid),

  UNIQUE (lfmt)
);


-- main table for unit tests
-- contains all one-one UT info
-- Need to update fail/warn comparison so they are ENUM
-- Need to extend so there are n-levels of warning
CREATE TABLE IF NOT EXISTS cuts.unit_tests (
  utid                      INT               NOT NULL auto_increment,
  name                      VARCHAR(45)       NOT NULL,
  description               VARCHAR(256),
  evaluation                VARCHAR(45)       NOT NULL,
  fail_comparison           VARCHAR(20),
  fail                      VARCHAR(25),
  warn_comparison           VARCHAR(20),
  warn                      VARCHAR(25),
  aggregration_function     VARCHAR(25)       NOT NULL,

  -- set the primary key for the table
  PRIMARY KEY  (utid),

  -- set the unique values for the table
  UNIQUE (name)
);

-- main table for packages


CREATE TABLE IF NOT EXISTS cuts.packages (
  id            INT               NOT NULL auto_increment,
  name          VARCHAR(95)       NOT NULL,

  -- set the constraints for the table
  PRIMARY KEY  (id),

  -- set the unique values for the table
  UNIQUE (name)
);

-- main table for test suites

CREATE TABLE IF NOT EXISTS cuts.test_suites (
  id            INT             NOT NULL auto_increment,
  name          VARCHAR(95)     NOT NULL,

  -- set the constraints for the table
  PRIMARY KEY  (id),

  -- set the unique values for the table
  UNIQUE (name)
);


-- sub table for log formats
-- contains variable info - name, type, id

CREATE TABLE IF NOT EXISTS cuts.log_format_variables (
  variable_id       INT            NOT NULL auto_increment,
  lfid              INT            NOT NULL,
  varname           VARCHAR(45)    NOT NULL,
  vartype           VARCHAR(45)    NOT NULL,

  -- set the constraints for the table
  PRIMARY KEY (variable_id),

  -- set the unique values for the table
  UNIQUE (lfid, varname),

  FOREIGN KEY (lfid) REFERENCES cuts.log_formats (lfid)
    ON DELETE CASCADE
    ON UPDATE CASCADE
);


-- sub table for packages
-- contains unit test ids

CREATE TABLE IF NOT EXISTS cuts.package_unit_tests (
  id            INT              NOT NULL auto_increment,
  ut_id         INT              NOT NULL,

  -- set the constraints for the table
  FOREIGN KEY (id) REFERENCES cuts.packages (id)
    ON DELETE CASCADE
    ON UPDATE CASCADE,

  FOREIGN KEY (ut_id) REFERENCES cuts.unit_tests (utid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,
  UNIQUE (id,ut_id)
);


-- sub table for test_suites
-- contains package ids

CREATE TABLE IF NOT EXISTS cuts.test_suite_packages (
  id              INT             NOT NULL,
  p_id            INT             NOT NULL,

  -- set the unique values for the constraint
  UNIQUE (id, p_id),

  -- set the foreign keys for the table
  FOREIGN KEY (id) REFERENCES cuts.test_suites (id)
    ON DELETE CASCADE
    ON UPDATE CASCADE,

  FOREIGN KEY (p_id) REFERENCES cuts.packages (id)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);


-- sub table for unit tests
-- will contain relation info

CREATE TABLE IF NOT EXISTS cuts.unit_test_relations (
  utid          INT                NOT NULL,
  variable_id   INT                NOT NULL,
  variable_id_2 INT                NOT NULL,

  -- set the constraints for the table
  PRIMARY KEY (utid),

  FOREIGN KEY (utid) REFERENCES cuts.unit_tests (utid)
    ON DELETE CASCADE
    ON UPDATE CASCADE,

  FOREIGN KEY (variable_id)
    REFERENCES cuts.log_format_variables (variable_id)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,

  FOREIGN KEY (variable_id_2)
    REFERENCES cuts.log_format_variables (variable_id)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

-- sub table for unit tests
-- contains log format ids

CREATE TABLE IF NOT EXISTS cuts.unit_test_log_formats (
  utid          INT           NOT NULL,
  lfid          INT           NOT NULL,

  UNIQUE (utid, lfid),

  FOREIGN KEY (utid) REFERENCES cuts.unit_tests (utid)
    ON DELETE CASCADE
    ON UPDATE CASCADE,

  FOREIGN KEY (lfid) REFERENCES cuts.log_formats (lfid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

-- ============================================================================
-- BEGIN STORED PROCEDURES
-- ============================================================================

DELIMITER //

-- given lfid gets all info about that LF - regex, varname/type/extended name

DROP PROCEDURE IF EXISTS cuts.select_log_format_information//

CREATE PROCEDURE
  cuts.select_log_format_information (IN lfid_in INT)
BEGIN
      -- When Databinding, the created column needs to have a type
      -- given to it, or it will not be able to bind correctly
      select csharp_regex,variable_id,varname,vartype, CAST(concat("LF",log_formats.lfid,".",varname) AS CHAR) as extended_varname
      FROM log_formats join log_format_variables on log_formats.lfid = log_format_variables.lfid
      where log_formats.lfid = lfid_in;
END //


-- given lfid returns messages from log that match that lfid

DROP PROCEDURE IF EXISTS cuts.select_log_data//

CREATE PROCEDURE
  cuts.select_log_data(IN lfid_in INT)

BEGIN
    select test_number,message from msglog where message regexp (SELECT icase_regex from log_formats WHERE lfid = lfid_in);
END //

DROP PROCEDURE IF EXISTS cuts.select_unit_test_log_formats //

CREATE PROCEDURE cuts.select_unit_test_log_formats (IN utid_ INT)
BEGIN
  SELECT t1.lfid, csharp_regex
    FROM cuts.unit_test_log_formats AS t1, cuts.log_formats AS t2
    WHERE utid = utid_ AND
          t1.lfid = t2.lfid;
END //

DROP PROCEDURE IF EXISTS cuts.select_log_data_by_test //

CREATE PROCEDURE
  cuts.select_log_data_by_test (IN test_number_ INT,
                                IN format_ INT)

BEGIN
  SELECT hostname, msgtime, severity, message
    FROM cuts.msglog AS t1, cuts.ipaddr_host_map AS t2
    WHERE test_number = test_number_ AND
          t1.hostid = t2.hostid AND
          message REGEXP (SELECT icase_regex FROM cuts.log_formats WHERE lfid = format_)
    ORDER BY hostname, t1.msgtime;
END //

DROP FUNCTION IF EXISTS cuts.get_qualified_variable_name //

CREATE FUNCTION cuts.get_qualified_variable_name (var_ INT)
  RETURNS VARCHAR (256)
BEGIN
  DECLARE retval VARCHAR (256);

  SELECT CONCAT('LF', CAST(lfid AS CHAR), '.', varname) AS fq_name
    INTO retval
    FROM cuts.log_format_variables
    WHERE variable_id = var_;

  RETURN retval;
END //

DROP FUNCTION IF EXISTS cuts.get_variable_owner //

CREATE FUNCTION cuts.get_variable_owner (varid_ INT)
  RETURNS VARCHAR (64)
BEGIN
  DECLARE retval VARCHAR (64);

  SELECT CONCAT('LF', CAST(lfid AS CHAR))
    INTO retval
    FROM cuts.log_format_variables
    WHERE variable_id = varid_;

  return retval;
END //

DROP PROCEDURE IF EXISTS cuts.select_unit_test_variables //

CREATE PROCEDURE cuts.select_unit_test_variables (IN utid_ INT)
BEGIN
  SELECT
    lfid, vartype, varname, CONCAT('LF', CAST(lfid AS CHAR), '.', varname) AS fq_name
    FROM cuts.log_format_variables
    WHERE lfid IN (SELECT lfid FROM cuts.unit_test_log_formats WHERE utid = utid_);
END //

DROP PROCEDURE IF EXISTS cuts.select_unit_test_relations_as_set //

CREATE PROCEDURE cuts.select_unit_test_relations_as_set (IN utid_ INT)
BEGIN
  SELECT cuts.get_qualified_variable_name (variable_id) AS lhs,
         cuts.get_qualified_variable_name (variable_id_2) AS rhs
    FROM cuts.unit_test_relations
    WHERE utid = utid_;
END //

DROP PROCEDURE IF EXISTS cuts.select_unit_test_relations_as_sql //

CREATE PROCEDURE cuts.select_unit_test_relations_as_sql (IN utid_ INT)
BEGIN
  SELECT CONCAT(cuts.get_qualified_variable_name (variable_id),
                ' = ',
                cuts.get_qualified_variable_name (variable_id_2)) AS relation
    FROM cuts.unit_test_relations
    WHERE utid = utid_;
END //

-- Simply inserts a relation into a unit test

DROP PROCEDURE IF EXISTS cuts.insert_unit_test_relation//
CREATE PROCEDURE
  cuts.insert_unit_test_relation (IN utid_in  INT,
                           IN vid_1_in INT,
                           IN vid_2_in INT)
BEGIN
      INSERT INTO unit_test_relations (utid,variable_id,variable_id_2) VALUES (utid_in, vid_1_in, vid_2_in);
END //

-- Allows you to grab all the results of a unit test, filtered by a test
--   number

DROP PROCEDURE IF EXISTS cuts.evaluate_unit_test_as_metric//
CREATE PROCEDURE
  cuts.evaluate_unit_test_as_metric(IN utid_in INT,
                                    IN test_num INT )
BEGIN
    DECLARE fail_op             VARCHAR(2);
    DECLARE fail_val            VARCHAR(10);
    DECLARE warn_op             VARCHAR(2);
    DECLARE warn_val            VARCHAR(10);
    DECLARE tablename           VARCHAR(90);
    DECLARE single_tablename    VARCHAR(90);
    DECLARE eval                VARCHAR(150);
    DECLARE lfid_count          INT;

    DECLARE temp                VARCHAR(10);
    DECLARE t_var1              VARCHAR(45);
    DECLARE t_var2              VARCHAR(45);

    DECLARE debugger            VARCHAR(1024);

    -- See if we are working on a two LF unit test, or a normal one
    SELECT COUNT(*)
      INTO lfid_count
      FROM cuts.unit_test_log_formats
      WHERE utid = utid_in;

    SELECT   fail_comparison, fail,     warn_comparison, warn,     evaluation
      INTO   fail_op,         fail_val, warn_op,         warn_val, eval
      FROM unit_tests
      WHERE utid = utid_in;

    IF lfid_count = 1 THEN
            SELECT CONCAT("LF",lfid), CONCAT("LF",lfid)
                INTO tablename,        single_tablename
                FROM cuts.unit_test_log_formats
                WHERE utid = utid_in;
    ELSEIF lfid_count = 2 THEN

            SELECT lfid, CONCAT("LF",lfid)
              INTO temp, single_tablename
              FROM cuts.unit_test_log_formats
              WHERE utid = utid_in
              LIMIT 1;

            SELECT lfid
              INTO tablename
              FROM cuts.unit_test_log_formats
              WHERE utid = utid_in
              LIMIT 1,1;

            SELECT CONCAT("LF",lfid,".",varname)
              INTO t_var1
              FROM log_format_variables
              WHERE variable_id=( SELECT variable_id
                                    FROM unit_test_relations
                                    WHERE utid=utid_in );

            SELECT CONCAT("LF",lfid,".",varname)
              INTO t_var2
              FROM log_format_variables
              WHERE variable_id=( SELECT variable_id_2
                                    FROM unit_test_relations
                                    WHERE utid=utid_in );


            SELECT CONCAT("LF",temp," JOIN LF",tablename," ON ",
              t_var1,"=",t_var2)
              INTO tablename;
    END IF;

    SELECT CONCAT("
        SELECT (",eval,") AS evaluation ",
          "FROM ", tablename," ",
          "WHERE ", single_tablename,".test_number=",test_num,";"
        ) INTO debugger;

    SET @sql = CONCAT("
        SELECT (",eval,") AS evaluation ",
          "FROM ", tablename," ",
          "WHERE ", single_tablename,".test_number=",test_num,";"
        );


    PREPARE s1 FROM @sql;
    EXECUTE s1;
    DEALLOCATE PREPARE s1;
END//

DROP PROCEDURE IF EXISTS cuts.insert_log_format//
CREATE PROCEDURE
  cuts.insert_log_format(IN log_form VARCHAR(150),
                 IN iregex VARCHAR(180),
                 IN csregex VARCHAR(180))
BEGIN
    INSERT INTO log_formats (lfmt,icase_regex,csharp_regex) VALUES (log_form, iregex, csregex);
    SELECT lfid FROM  log_formats WHERE lfmt = log_form;
END //



DROP PROCEDURE IF EXISTS cuts.insert_log_format_variable//
CREATE PROCEDURE
  cuts.insert_log_format_variable(IN id INT,
                          IN name VARCHAR(45),
                          IN vtype VARCHAR(45))
BEGIN
    INSERT INTO log_format_variables (lfid, varname, vartype) VALUES (id,name,vtype);
END //


-- given package id and utid - inserts unit test in package
DROP PROCEDURE IF EXISTS cuts.insert_package_unit_test//
CREATE PROCEDURE
  cuts.insert_package_unit_test(IN id_in integer,
                                IN utid_in integer)
BEGIN
      insert into package_unit_tests (id, ut_id) values (id_in, utid_in);
END //

-- given a name, it inserts that as a test suite

DROP PROCEDURE IF EXISTS cuts.insert_test_suite//
CREATE PROCEDURE
  cuts.insert_test_suite(IN name_in VARCHAR(65))
BEGIN
    Insert into test_suites (name) values (name_in);
END //


-- given a test suite id and name, this inserts the name as a new package, and then inserts that package into the test suite

DROP PROCEDURE IF EXISTS cuts.insert_test_suite_package//
CREATE PROCEDURE
  cuts.insert_test_suite_package(IN tsid INT,
                                 IN pkg_name VARCHAR(65))
BEGIN
  INSERT INTO test_suite_packages (id, p_id)
    VALUES (tsid,
            cuts.get_test_package_id (pkg_name));
END //


DROP PROCEDURE IF EXISTS cuts.create_test_package //

CREATE PROCEDURE
  cuts.create_test_package (IN pkg_name VARCHAR (65))
BEGIN
  INSERT INTO cuts.packages (name) VALUES (pkg_name);
END //

DROP FUNCTION IF EXISTS cuts.get_test_package_id //

CREATE FUNCTION
  cuts.get_test_package_id (pkg_name VARCHAR (65))
  RETURNS INT
BEGIN
  DECLARE retval INT;

  DECLARE CONTINUE HANDLER FOR NOT FOUND
  BEGIN
    INSERT INTO cuts.packages (name) VALUES (pkg_name);
    SET retval = LAST_INSERT_ID();
  END;

  SELECT id INTO retval FROM cuts.packages WHERE name = pkg_name;
  RETURN retval;
END //

-- given test suite id and package id, inserts package into test suite

DROP PROCEDURE IF EXISTS cuts.insert_test_suite_package_existing//
CREATE PROCEDURE
  cuts.insert_test_suite_package_existing(IN id_in integer,
                                          IN pid_in integer)
BEGIN
      insert into test_suite_packages (id,p_id) values (id_in, pid_in);
END //


-- given 1-1 data for unit test, inserts new UT and returns id

DROP PROCEDURE IF EXISTS cuts.insert_unit_test//
CREATE PROCEDURE cuts.insert_unit_test(IN name_in VARCHAR(45),
                                IN descr VARCHAR(95),
                                IN fail_comp VARCHAR(20),
                                IN warn_comp VARCHAR(20),
                                IN eval VARCHAR(150),
                                IN fail VARCHAR(25),
                                IN warn VARCHAR(25),
                                IN aggr VARCHAR(25))
BEGIN
    INSERT INTO cuts.unit_tests (name,
                                   description,
                                   fail_comparison,
                                   warn,fail,
                                   evaluation,
                                   warn_comparison,
                                   aggregration_function)
                           VALUES (name_in,
                                   descr,
                                   fail_comp,
                                   warn,
                                   fail,
                                   eval,
                                   warn_comp,
                                   aggr);

    SELECT utid FROM unit_tests WHERE name = name_in;
END //


-- given utid and lfid, add log format to ut

DROP PROCEDURE IF EXISTS cuts.insert_unit_test_log_format//
CREATE PROCEDURE
  cuts.insert_unit_test_log_format(IN utid_in INT,
                           IN lfid_in INT)
BEGIN
    INSERT INTO unit_test_log_formats (utid, lfid)
      VALUES (utid_in, lfid_in);
END //

DELIMITER ;
