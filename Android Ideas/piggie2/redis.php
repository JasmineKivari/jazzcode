<?php
$redis = new Redis();
$redis->connect('10.10.10.3', 6379);
$redis->setOption(Redis::OPT_SERIALIZER, Redis::SERIALIZER_IGBINARY);

?>
