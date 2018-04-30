<?php
require_once("redis.php");

$redis->set('testKey1', 100);
if ($redis->exists('testKey1')) {
       $val = $redis->get('testKey1');
       echo $val;
} else {
       echo 'Key did not exist.';
}

?>
