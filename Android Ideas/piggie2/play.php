<?php

require_once('database.php');
require_once('redis.php');

$id = $_REQUEST["id"];
$gid = $_REQUEST["gid"];
$bet = $_REQUEST["bet"];
//$wp = $_REQUEST["wp"];


$sql = 'INSERT INTO user_game_data (user_id, game_id, k, v) VALUES ';
$sql = $sql . "($id, $gid, 'last_play', now()) ";
$sql = $sql . "ON DUPLICATE KEY UPDATE v = now()";
$retval = $conn->query( $sql );
if(! $retval )
{	
	$m = "Could not update last_play: " . $conn->error;
        error_log($m);
	die('{"status":"error", "message":"' . $m . '"}');
}



// New Get the win percent for this game.
$gameDataKey = "game.data.$gid";
if ($redis->exists($gameDataKey)) {
    $gameData = $redis->get($gameDataKey);
} else {
	$gameData = [];
	$sql = "SELECT k, v FROM game_data WHERE game_id = $gid";
	$retval = $conn->query( $sql);
	if(! $retval )
	{	
		$m = "Could not retrieve stats from game_data: " . $conn->error;
			error_log($m);
		die('{"status":"error", "message":"' . $m . '"}');
	}
	//$wp = 0;
	while ($row = $retval->fetch_assoc())
	{
		$gameData[$row[“k”]] = $row[“v”];
	}
	$redis->set($gameDataKey, $gameData);
}
$wp = floatval($gameData["wp"]);



$userGameDataKey = "user.game.$id.$gid";
if ($redis->exists($userGameDataKey)) {
	$userGameData = $redis->get($userGameDataKey);
} else {
	$userGameData = [];
	$sql = "SELECT k, v FROM user_game_data WHERE user_id = $id AND game_id = $gid";
	$retval = $conn->query( $sql);
	if(! $retval )
	{	
		$m = "Could not retrieve stats from user_game_data: " . $conn->error;
        error_log($m);
		die('{"status":"error", "message":"' . $m . '"}');
	}
	$win_count = 0;
	$lose_count = 0;
	$win_total = 0;
	$lose_total = 0;
	while ($row = $retval->fetch_assoc())
	{
		$userGameData[$row[“k”]] = $row[“v”];
		
	}
	$redis->set($userGameDataKey, $userGameData);
}
	$win_count = 0;
	$lose_count = 0;
	$win_total = 0;
	$lose_total = 0;
if (array_key_exists("win_count", $userGameData)) {
	$win_count = intval($userGameData["win_count"]);
} else {
	$userGameData["win_count"] = '0';
}
if (array_key_exists("lose_count", $userGameData)) {
	$lose_count = intval($userGameData["lose_count"]);
} else {
	$userGameData["lose_count"] = '0';
}
if (array_key_exists("win_total", $userGameData)) {
	$win_total = intval($userGameData["win_total"]);
} else {
	$userGameData["win_total"] = '0';
}
if (array_key_exists("lose_total", $userGameData)) {
	$lose_total = intval($userGameData["lose_total"]);
} else {
	$userGameData["lose_total"] = '0';
}


$delta_coins = (rand()/getrandmax() < $wp/2) ? $bet : -$bet;
$delta_xp = intval($bet);
$delta_level = (rand()/getrandmax() < 0.005) ? 1 : 0; // level-up 1 in 200 plays on average

if ($delta_coins > 0)
{
	$count_key = "win_count";
	$total_key = "win_total";
	$count_value = $win_count + 1;
	$total_value = $win_total + $delta_coins;
}
else
{
	$count_key = "lose_count";
	$total_key = "lose_total";
	$count_value = $lose_count + 1;
	$total_value = $lose_total - $delta_coins;
}
$sql = "INSERT INTO user_game_data (user_id, game_id, k, v) ";
$sql .= "VALUES ($id, $gid, '$count_key', '$count_value') ";
$sql .= "ON DUPLICATE KEY UPDATE v = '$count_value'";
$retval = $conn->query( $sql );
if(! $retval )
{	
	$m = "Could not update win/lose count in user_game_data: " . $conn->error;
        error_log($m);
	die('{"status":"error", "message":"' . $m . '"}');
}

$userGameData["win_count"] = strval($win_count);
$userGameData["lose_count"] = strval($lose_count);
$userGameData["win_total"] = strval($win_total);
$userGameData["lose_total"] = strval($lose_total);
$redis->set("user.game.$id.$gid", $userGameData);


$win_total = $win_total + $delta_coins;
$sql = "INSERT INTO user_game_data (user_id, game_id, k, v) ";
$sql .= "VALUES ($id, $gid, '$total_key', '$total_value') ";
$sql .= "ON DUPLICATE KEY UPDATE v = '$total_value'";
$retval = $conn->query( $sql );
if(! $retval )
{
        $m = "Could not update win/lose total in user_game_data: " . $conn->error;
        error_log($m);
	die('{"status":"error", "message":"' . $m . '"}');
}	

$userGameData["win_count"] = strval($win_count);
$userGameData["lose_count"] = strval($lose_count);
$userGameData["win_total"] = strval($win_total);
$userGameData["lose_total"] = strval($lose_total);
$redis->set("user.game.$id.$gid", $userGameData);


$sql = "UPDATE users SET xp=xp+$delta_xp, coins=coins+$delta_coins, level=level+$delta_level WHERE id=$id";
$retval = $conn->query( $sql );
if(! $retval )
{
        $m = "Could not update users table with play result: " . $conn->error;
        error_log($m);
	die('{"status":"error", "message":"' . $m . '"}');
}

$userGameData["win_count"] = strval($win_count);
$userGameData["lose_count"] = strval($lose_count);
$userGameData["win_total"] = strval($win_total);
$userGameData["lose_total"] = strval($lose_total);
$redis->set("user.game.$id.$gid", $userGameData);



$result = [];

$result["status"] = "success";
$result["delta_coins"] = $delta_coins;
$result["delta_xp"] = $delta_xp;
$result["delta_level"] = $delta_level;


echo json_encode($result);
$conn->close();
?>

