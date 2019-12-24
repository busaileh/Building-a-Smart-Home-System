
<?php
//Script only sends, script will not recieve

/*
Before unsetting the session make sure that last entry gotten doesnt equals the entry gotten now
else you would want to send the command again and wait for the DB data 
if third time didnt work give an option to reset device
or check for device by sendd a command to make it beep
*/
session_start();

$link = mysqli_connect("localhost","raspberry","helloworld","raspberry");

if(mysqli_connect_error()){
	echo("Connection lost");
	die;
}

//if($tempRes = (mysqli_query($link,$query1))){
function getTemprature(){
	//shell_exec("sudo -S python python/main.py 001 status);
	if($_SESSION){
		if(array_key_exists("device1",$_SESSION)){
			unset($_SESSION["device1"]);

		}
	}
	include("connection.php");
	//Here run the python script that gets the temp and updates in DB
	shell_exec("sudo -S python python/main.py get data 1");
	$query = "select * from temprature where entry = (select max(entry) from temprature)";
	
	if($result = (mysqli_query($link,$query))){
		$row = mysqli_fetch_array($result);
		//$row = array_values($row);
		$_SESSION["device1"] = $row;
		$json = json_encode($row);
		echo($json);
	}
}

function getCooridor(){
	shell_exec("sudo -S python python/main.py 010 status");
	sleep(2);
	if($_SESSION){
		if(array_key_exists("device2",$_SESSION)){
			unset($_SESSION["device2"]);

		}
	}
	include("connection.php");
	$query = "select * from corridor where entry= (select max(entry) from corridor)";
	if($result = (mysqli_query($link,$query))){
		$row = mysqli_fetch_array($result);
		$_SESSION["device2"] = $row;
		//$row = array_values($row);
		$json = json_encode($row);
		echo($json);
	}
}

function getLivingRoom(){
	shell_exec("sudo -S python python/main.py 011 status");
	sleep(2);
	if($_SESSION){
		if(array_key_exists("device3",$_SESSION)){
			unset($_SESSION["device3"]);

		}
	}
	include("connection.php");
	$query = "select * from livingroom where entry= (select max(entry) from livingroom)";
	if($result = (mysqli_query($link,$query))){
		$row = mysqli_fetch_array($result);
		$_SESSION["device3"] = $row;
		$json = json_encode($row);
		echo($json);
	}
}


function getRoom(){
	
	shell_exec("sudo -S python python/main.py 100 status");
	sleep(2);
	
	if($_SESSION){
		if(array_key_exists("device4",$_SESSION)){
			unset($_SESSION["device4"]);
		}
	}
	
	include("connection.php");
	$query = "select * from room where entry= (select max(entry) from room)";
	if($result = (mysqli_query($link,$query))){
		
		$row = mysqli_fetch_array($result);
		$_SESSION["device4"] = $row;
		$json = json_encode($row);
		echo($json);
	}

}

function updateStatus($device){

	if($device == "1" or $device == "001"){
		getTemprature();
	}else if($device =="2" or $device == "010"){
		getCooridor();
	}else if($device == "3" or $device == "011"){
		getLivingRoom();
	}else if($device == "4" or $device == "100"){
		getRoom();
	}else if($device == "all"){
		sleep(1);
		include("phpscripts/getdata.php");
	}
	
}
function sendData($device,$data){
	//In the send data just send the device + $data as they are script will do the rest 
	//echo("sudo -S python /python/Sending/main.py $device $data");
	shell_exec("sudo -S python python/main.py $device $data");
	
}

function proccessData($device,$value){
	$msg = "";
	#echo("value is $value<br>");
		
	switch ($value) {
		case "lighton":
			$msg = "lon";
				break;
		case "lightoff":
			$msg = "loff";
				break;
		case "tvon":
			$msg = "ton";
			break;
		case "tvoff":
			$msg = "toff";
			break;
		case "turnOffDevices":
			$device = "all";
			$msg = "off";
			break;
			
		case "turnOffAll":
			$device = "all";
			$msg = "loff";
			break;
			
		case "turnOnAll":
			$device = "all";
			$msg = "lon";
			break;
		default:
				$msg = $value;
				break;
	}
	
	if($msg != ""){
		
		sendData($device,$msg);
		if($device =="all"){
			updateStatus($device);
		} else{
			sleep(2);
			updateStatus($device);
		}
	}
	
}

include("scriptdetermine.php");

if(isAjax()){
	if(getOrPost() == "get"){
		//If its a get (get status)
		$device = getDevice();
		updateStatus($device);
		
	} else if(getOrPost() == "post"){
		//if its a post every device has his own thing
		if(array_key_exists("value",$_POST) && array_key_exists("device",$_POST)){
			
			$value = $_POST["value"];
			$device = $_POST["device"];
			$device = getDeviceForSending($device);
			proccessData($device,$value);

		} else {
			echo("Nothing found");}
		
		
		//We will send the data and wait for the Raspi to recieve and put in DB
		
	}
	
	
}



?>