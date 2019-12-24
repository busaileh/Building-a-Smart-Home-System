<?php
function isAjax(){
	if(array_key_exists("HTTP_X_REQUESTED_WITH",$_SERVER) and $_SERVER["HTTP_X_REQUESTED_WITH"] =="AJAX"){
		return true;
	}else{
		return false;
	}
}
function getOrPost(){
	if($_SERVER['REQUEST_METHOD'] == "GET" and isset($_GET["device"])){
		return "get";
	}else if($_SERVER['REQUEST_METHOD'] == "POST" ){
		return "post";
	}
}
function getDevice(){
	if($_GET){
		if(array_key_exists("device",$_GET)){
			if($_GET["device"] == "device1"){
				return "1";
			} else if($_GET["device"] == "device2"){
				return "2";
			} else if($_GET["device"] == "device3"){
				return "3";
			} else if($_GET["device"] == "device4"){
				return "4";
			}
		}
	} 
}
function getDeviceForSending($device){
	if($device == "device1"){
		return "001";
		
	} else if($device == "device2"){
		return "010";
		
	} else if($device == "device3"){
		return "011";
		
	} else if($device == "device4"){
		return "100";
	}
		
}
?>