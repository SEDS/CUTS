--
-- @file        CUTS-baseline.sql
--
-- $Id$
--
-- @author      James H. Hill
--

USE cuts;

--
-- Create the baseline table. This table contains baseline
-- metric information to each component instance type,
-- per host.
--

CREATE TABLE IF NOT EXISTS baseline
(
  bid             INT             NOT NULL auto_increment,
  instance        INT             NOT NULL,
  host            INT             NOT NULL,
  inport          INT             NOT NULL,
  outport         INT,
  metric_type     ENUM ('transit',
                        'queue',
                        'process')  NOT NULL,
  event_count     INT,
  best_time       INT,
  worst_time      INT,
  total_time      INT,

  -- set the primary key
  PRIMARY KEY (bid),

  -- set the unique keys
  UNIQUE (instance, host, metric_type, inport, outport),

  -- set the foreign key(s)
  FOREIGN KEY (instance) REFERENCES component_instances (component_id)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,

  FOREIGN KEY (host) REFERENCES ipaddr_host_map (hostid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,

  FOREIGN KEY (inport) REFERENCES ports (pid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,

  FOREIGN KEY (outport) REFERENCES ports (pid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

DELIMITER //

-------------------------------------------------------------------------------
-- FUNCTION: cuts.get_component_baseline_id
-------------------------------------------------------------------------------

DROP FUNCTION IF EXISTS cuts.get_component_baseline_id //

CREATE FUNCTION cuts.get_component_baseline_id (
  hid INT, inst INT, mtype VARCHAR (10), iid INT, oid INT)
  RETURNS INT
BEGIN
  DECLARE baseline_id INT;

  SELECT bid INTO baseline_id FROM cuts.baseline
    WHERE (host = hid AND instance = inst AND metric_type = mtype AND
           inport = iid AND outport = oid);

  RETURN baseline_id;
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_baseline
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_baseline //

CREATE PROCEDURE
  cuts.insert_component_baseline (
    IN hid INT,
    IN inst VARCHAR (255),
    IN mtype VARCHAR (10),
    IN inport VARCHAR (255),
    IN outport VARCHAR (255),
    IN ec INT,
    IN bt INT,
    IN wt INT,
    IN tt INT)
BEGIN
  DECLARE tid INT;
  DECLARE cid INT;
  DECLARE iid INT;
  DECLARE oid INT;
  DECLARE baseline_id INT;

  -- get the type id of the component
  SELECT typeid INTO tid FROM component_instances
    WHERE component_name = inst LIMIT 1;

  -- get the id of the sender and current component
  SELECT component_id INTO cid FROM component_instances
    WHERE component_name = inst;

  SELECT pid INTO iid FROM ports
    WHERE ctype = tid AND portid =
      (SELECT portid FROM portnames WHERE portname = inport)
      AND port_type = 'sink';

  SELECT pid INTO oid FROM ports
    WHERE ctype = tid AND portid =
      (SELECT portid FROM portnames WHERE portname = outport)
      AND port_type = 'source';

  -- determine if the baseline already exists
  SET baseline_id =
    cuts.get_component_baseline_id (hid, cid, mtype, iid, oid);

  IF NOT baseline_id IS NULL THEN
    -- update an existing baseline metric
    UPDATE cuts.baseline
      SET event_count = ec, best_time = bt, worst_time = wt, total_time = tt
      WHERE bid = baseline_id;
  ELSE
    -- create a new baseline metric
    INSERT INTO cuts.baseline (instance, host, metric_type, inport, outport,
      event_count, best_time, worst_time, total_time)
      VALUES (cid, hid, mtype, iid, oid, ec, bt, wt, tt);
  END IF;
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_baseline_using_ipaddr
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_baseline_using_ipaddr //

CREATE PROCEDURE
  cuts.insert_component_baseline_using_ipaddr (
    IN ip_addr VARCHAR (40),
    IN inst VARCHAR (255),
    IN mtype VARCHAR (10),
    IN inport VARCHAR (255),
    IN outport VARCHAR (255),
    IN ec INT,
    IN bt INT,
    IN wt INT,
    IN tt INT)
BEGIN
  DECLARE hid INT;

  SELECT hostid INTO hid FROM ipaddr_host_map
    WHERE ipaddr = ip_addr;

  CALL insert_component_baseline(hid, inst, mtype, inport, outport, ec, bt, wt, tt);
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_baseline_using_hostname
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_baseline_using_hostname //

CREATE PROCEDURE
  cuts.insert_component_baseline_using_hostname (
    IN host VARCHAR (40),
    IN inst VARCHAR (255),
    IN mtype VARCHAR (10),
    IN inport VARCHAR (255),
    IN outport VARCHAR (255),
    IN ec INT,
    IN bt INT,
    IN wt INT,
    IN tt INT)
BEGIN
  DECLARE hid INT;

  SELECT hostid INTO hid FROM ipaddr_host_map
    WHERE hostname = host;

  CALL insert_component_baseline(hid, inst, mtype, inport, outport, ec, bt, wt, tt);
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_baseline_default
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_baseline_default //

CREATE PROCEDURE
  cuts.insert_component_baseline_default (
    IN inst VARCHAR (255),
    IN mtype VARCHAR (10),
    IN inport VARCHAR (255),
    IN outport VARCHAR (255),
    IN ec INT,
    IN bt INT,
    IN wt INT,
    IN tt INT)
BEGIN
  CALL insert_component_baseline_using_hostname ('unknown',
                                                 inst,
                                                 mtype,
                                                 inport,
                                                 outport,
                                                 ec,
                                                 bt,
                                                 wt,
                                                 tt);
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_baseline_metrics_all
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.select_baseline_metric_all //

CREATE PROCEDURE
  cuts.select_baseline_metric_all ()
BEGIN
  SELECT t7.*, t8.portname AS source FROM
    (SELECT t5.*, t6.portname AS sink FROM
      (SELECT t3.*, t4.hostname FROM
        (SELECT t1.*, (t1.total_time / t1.event_count) AS avg_time, t2.component_name
          FROM baseline AS t1
          LEFT JOIN component_instances AS t2 ON t1.instance = t2.component_id) AS t3
        LEFT JOIN ipaddr_host_map AS t4 ON t3.host = t4.hostid) AS t5
      LEFT JOIN (SELECT pid, portname
        FROM ports, portnames
          WHERE ports.portid = portnames.portid) AS t6 ON t5.inport = t6.pid) AS t7
    LEFT JOIN (SELECT pid, portname
        FROM ports, portnames
          WHERE ports.portid = portnames.portid) AS t8 ON t7.outport = t8.pid
    ORDER BY component_name;
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_baseline_metric_for_test
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.select_baseline_metric_for_test //

CREATE PROCEDURE
  cuts.select_baseline_metric_for_test (IN test INT)
BEGIN
  SELECT DISTINCT t10.component, t9.* FROM execution_time AS t10
    LEFT JOIN (SELECT t7.*, t8.portname AS source FROM
      (SELECT t5.*, t6.portname AS sink FROM
        (SELECT t3.*, t4.hostname FROM
          (SELECT t1.*, (t1.total_time / t1.event_count) AS avg_time, t2.component_name
            FROM baseline AS t1
            LEFT JOIN component_instances AS t2 ON t1.instance = t2.component_id) AS t3
          LEFT JOIN ipaddr_host_map AS t4 ON t3.host = t4.hostid) AS t5
        LEFT JOIN (SELECT pid, portname
          FROM ports, portnames
            WHERE ports.portid = portnames.portid) AS t6 ON t5.inport = t6.pid) AS t7
      LEFT JOIN (SELECT pid, portname
          FROM ports, portnames
            WHERE ports.portid = portnames.portid) AS t8 ON t7.outport = t8.pid) AS t9
      ON t9.instance = t10.component
      WHERE t10.test_number = test
      ORDER BY component_name;
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_baseline_metric_for_test_by_time
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.select_baseline_metric_for_test_by_time //

CREATE PROCEDURE
  cuts.select_baseline_metric_for_test_by_time (IN test INT,
                                                IN coll DATETIME)
BEGIN
  SELECT DISTINCT t10.component, t9.* FROM execution_time AS t10
    LEFT JOIN (SELECT t7.*, t8.portname AS source FROM
      (SELECT t5.*, t6.portname AS sink FROM
        (SELECT t3.*, t4.hostname FROM
          (SELECT t1.*, (t1.total_time / t1.event_count) AS avg_time, t2.component_name
            FROM baseline AS t1
            LEFT JOIN component_instances AS t2 ON t1.instance = t2.component_id) AS t3
          LEFT JOIN ipaddr_host_map AS t4 ON t3.host = t4.hostid) AS t5
        LEFT JOIN (SELECT pid, portname
          FROM ports, portnames
            WHERE ports.portid = portnames.portid) AS t6 ON t5.inport = t6.pid) AS t7
      LEFT JOIN (SELECT pid, portname
          FROM ports, portnames
            WHERE ports.portid = portnames.portid) AS t8 ON t7.outport = t8.pid) AS t9
      ON t9.instance = t10.component
      WHERE t10.test_number = test AND t10.collection_time = coll
      ORDER BY component_name;
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_baseline_metric
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.select_baseline_metric //

CREATE PROCEDURE
  cuts.select_baseline_metric (IN instance_name VARCHAR (255))
BEGIN
  SELECT t7.*, t8.portname AS source FROM
    (SELECT t5.*, t6.portname AS sink FROM
      (SELECT t3.*, t4.hostname FROM
        (SELECT t1.*, (t1.total_time / t1.event_count) AS avg_time, t2.component_name
          FROM baseline AS t1
          LEFT JOIN component_instances AS t2 ON t1.instance = t2.component_id
          WHERE t2.component_name = instance_name) AS t3
        LEFT JOIN ipaddr_host_map AS t4 ON t3.host = t4.hostid) AS t5
      LEFT JOIN (SELECT pid, portname
        FROM ports, portnames
          WHERE ports.portid = portnames.portid) AS t6 ON t5.inport = t6.pid) AS t7
    LEFT JOIN (SELECT pid, portname
        FROM ports, portnames
          WHERE ports.portid = portnames.portid) AS t8 ON t7.outport = t8.pid;
END; //

DELIMITER ;
