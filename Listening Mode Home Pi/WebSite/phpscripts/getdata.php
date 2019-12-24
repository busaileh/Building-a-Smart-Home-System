<?php

session_start();


if($_SESSION){
	if(array_key_exists("device1",$_SESSION)){
		unset($_SESSION["device1"]);
	}
	if(array_key_exists("device2",$_SESSION)){
		unset($_SESSION["device2"]);
	}
	if(array_key_exists("device3",$_SESSION)){
		unset($_SESSION["device3"]);
	}
	if(array_key_exists("device4",$_SESSION)){
		unset($_SESSION["device4"]);
	}
}

//You want to get the Status off all 
//sudo python main.py all status
shell_exec("sudo -S python python/main.py all status");

sleep(3); // Sleep for one second untill data is here


$msg ="";


$link = mysqli_connect("localhost","raspberry","helloworld","raspberry");

if(mysqli_connect_error()){
	$msg .= "Connection lost";
	die;
}

$query1 = "select * from temprature where entry = (select max(entry) from temprature)";
$query2 = "select * from corridor where entry= (select max(entry) from corridor)";
$query3 = "select * from livingroom where entry= (select max(entry) from livingroom)";
$query4 = "select * from room where entry= (select max(entry) from room)";




$device1 = array();
$device2=array();
$device3=array();
$device4=array();
	

if($res = (mysqli_query($link,$query1))){
	$result = mysqli_fetch_array($res);
	if($result){
		$device1 = $result;
		$_SESSION["device1"] = $device1;
		
	}
	else{
		$msg."Error getting Device 1 Data";
	}
}

if($res = (mysqli_query($link,$query2))){
	
	$result = mysqli_fetch_array($res);
	if($result){
		$device2 = $result;
		$_SESSION["device2"] = $device2;
	}
	else{
		$msg."Error getting Device 2 Data";
	}
}

if($res = (mysqli_query($link,$query3))){
	
	$result = mysqli_fetch_array($res);
	if($result){
		$device3 = $result;
		$_SESSION["device3"] = $device3;
		
	}
	else{
		$msg."Error getting Device 3 Data";
	}
}

if($res = (mysqli_query($link,$query4))){
	
	$result = mysqli_fetch_array($res);
	if($result){
		$device4 = $result;
		$_SESSION["device4"] = $device4;
		
	}
	else{
		$msg."Error getting Device 4 Data";
	}
}


if($msg){
	echo($msg);
}
	






?>