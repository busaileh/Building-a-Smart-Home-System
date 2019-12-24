<?php

	session_start();

	$device1=array();
	$device2=array();
	$device3=array();
	$device4=array();
	
	if($_SESSION){
	if(isset($_SESSION["device1"])){
		
		
		$device1  = ($_SESSION["device1"]);
		//print_r($_SESSION["device1"]);
	}
	if(array_key_exists("device2",$_SESSION)){
		$device2 =($_SESSION["device2"]);
	}
	if(array_key_exists("device3",$_SESSION)){
		$device3 = ($_SESSION["device3"]);
	}
	if(array_key_exists("device4",$_SESSION)){
		$device4 = ($_SESSION["device4"]);
	}
		
}

?>


<html>
<head>
<meta charset="UTF-8">
<title>Untitled Document</title>
<link rel= "stylesheet" href="scripts/bootstrap/css/bootstrap.min.css">
	<style type="text/css">
		html{
			zoom = 100%;
		}

		.jumbotron{
			color:azure;
		}
		#jumboHeader{
			text-align: center;
		}

		#learnMore{
			float:right;
		}
		#para{
			margin-right: 10px;
		}
		#navHeader{
			background-color:#373A3C;
			border-bottom: 1px solid black;
			#height:65px;
		}
		#raspiLogo{
			width:40px;
			height:50px;
			position: relative;
			top:-5px;
		}

		#jumboContainer{
			background-color:#373A3C;
		}
		#signout{
			float:right;
			position: relative;
			top:-3px;
			color:white;

		}
		#items{
			padding:5px 0 0 100px;
		}
		#featuresButton{
			background: #373A3C;
			border:0px;
		}
		body{
			background: #A8A8A8;
		}
		#featuresPage{
			margin-top:50px;
			#display:none;
		}
		.container-features{
			
			background:white;

		}
		.device{
			float:left;
			width:350px;
			#border:2px solid black;
			text-align: center;
			margin:30px 0 30px 120px;
		}
		.cardImage{
			height:100px;
			width:100px;
			margin-top:10px;
			border:1px solid black;
			border-radius: 80%;
		}
		.card-block{
			margin:0;
			height:45px;
			#background:#91D4E2;
		}
		.updateButton{
			margin-top: 10px;
		}
	
		.controlButton{
			float:left;
			margin:5px 0 5px 65px;
		}
		.footer-buttons{
			height:70px;
			background:#F5F5F5;
		}
		
		
		.clearer{
			clear: both;

		}
		
		
		
		.list-group{
			margin-top:10px;
		}
	</style>
</head>

<body>



<?php include("items/navbar.php"); ?>
<?php include("items/jumptron.php");  ?>




<div class="container container-features">

	<div class="card device" id = "device1">
									<!---Temprature Device-->
		<div class = "card-block card-header">
			<h4 class="card-title">Temprature Monitor</h4>
		</div>
		<img class="card-img-top cardImage" src="images/temperature.jpg" alt="Card image cap"><br>
		<button class="btn btn-danger btn-sm status updateButton" value="status">Update Status</button>
		<ul class="list-group list-group-flush">
			<li class="list-group-item">Temprature: <strong id="temprature">
				<?php 
					//if(array_key_exists("temprature",$device1)){echo($device1['temprature']);
				if(is_array($device1)){
					if(array_key_exists("temprature",$device1)){
						echo($device1['temprature']);
					}
				}									   
				?>
			</strong></li>
			<li class="list-group-item">Humidity: <strong id="humidity">
				<?php if(is_array($device1)){
					if(array_key_exists("humidity",$device1)){
						echo($device1['humidity']);
				} }?>
			</strong></li>
			<li class="list-group-item">Last Updated:<strong id="lastUpdatedDevice1">
				<?php if(is_array($device1) and array_key_exists("date",$device1)){echo($device1['date']);}?>
			</strong></li>
		</ul>
	</div>
	
	
	<div class="card device" id="device2">
									<!---Corridor Device(Relay for now)-->
		<div class="card-block card-header">
			<h4 class="card-title">Corridor Control</h4>
		</div>
		<img class="card-img-top cardImage" src="images/locked.png" alt="Card image cap"><br>
		<button class="btn btn-danger status btn-sm updateButton" value="status">Update Status</button>
		<ul class="list-group list-group-flush">
			<li class="list-group-item ">Light is Currently: <strong id="lightStatusDevice2" class="light">
				<?php if(is_array($device2) and array_key_exists("light",$device2)){echo($device2['light']);}?>
			</strong></li>
			<li class="list-group-item">Door is:<strong id="doorStatus" class="door">
				<?php if(is_array($device2) and array_key_exists("door",$device2)){echo($device2['door']);}?>
			</strong></li>
			<li class="list-group-item">Home Security is: <strong id="homeSecurity" class="security">
				<?php if(is_array($device2) and array_key_exists("homesecuriety",$device2)){echo($device2['homesecuriety']);}?>
			</strong></li>
			<li class="list-group-item">Last Updated:<strong id="lastUpdatedDevice2">
				<?php if(is_array($device2) and array_key_exists("date",$device2)){echo($device2['date']);}?>
			</strong></li>
		</ul>

		
		<div class="footer-buttons">
			<button class="btn btn-danger control btn-sm controlButton" value="lighton" id="lightOnDevice2">Light On</button>
			<button class="btn btn-danger control btn-sm controlButton" value="secure" id="securityOn"> Secure</button>
			<div class="clearer"></div>
			<button class="btn btn-danger control btn-sm controlButton" value="lightoff" id="lightOffDevice2">Light Off</button>
			<button class="btn btn-danger control btn-sm controlButton" value="unsecure" id = "securityOff"> Unsecure</button>
		</div>
		

		
		
		
		
		
		
		
		
		
		
	</div>	
	
	<div style="clear: both;"></div>
	
	
	<div class="card device" id="device3">
									<!---Living Room Device(Relay for now)-->
		<div class="card-block card-header">
			<h4 class="card-title">Living Room Control</h4>
		</div>
		<img class="card-img-top cardImage" src="images/lighton.png" alt="Card image cap"><br>
		<button class="btn btn-danger status btn-sm updateButton" value="status">Update Status</button>
		
		<ul class="list-group list-group-flush">
			<li class="list-group-item ">Light is Currently: <strong id="lightStatusDevice3" class="light">
				<?php if(is_array($device3) and array_key_exists("light",$device3)){echo($device3['light']);}?>
			</strong></li>
			<li class="list-group-item">TV is:&nbsp;<strong id="tv">
				<?php if(is_array($device3) and array_key_exists("tv",$device3)){echo($device3['tv']);}?>
			</strong></li>
			<li class="list-group-item">Last Updated:<strong id="lastUpdatedDevice3">
				<?php if(is_array($device3) and array_key_exists("date",$device3)){echo($device3['date']);}?>
			</strong></li>
		</ul>
		<div class="footer-buttons">
			<button class="btn btn-danger control btn-sm controlButton" value="lighton" id="lightOnDevice3">Light On</button>
			<button class="btn btn-danger control btn-sm controlButton" value="tvon" id="tvOn">TV On</button>
			<button class="btn btn-danger control btn-sm controlButton" value="lightoff" id="lightOffDevice3">Light Off</button>
			<button class="btn btn-danger control btn-sm controlButton" value="tvoff" id="tvOff">TV Off</button>
		</div>
		
	</div>	
	
	
	
	<div class="card device" id="device4">
									<!---Corridor Device(Relay for now)-->
		<div class="card-block card-header">
			<h4 class="card-title">Room Control</h4>
		</div>
		<img class="card-img-top cardImage" src="images/lighton.png" alt="Card image cap"><br>
		<button class="btn btn-danger status btn-sm updateButton" value="status">Update Status</button>
		<ul class="list-group list-group-flush">
			
			<li class="list-group-item">Light is Currently: <strong id="lightStatusDevice4" class="light">
				<?php if(is_array($device4) and array_key_exists("light",$device4)){echo($device4['light']);}?>
			</strong></li>
			<li class="list-group-item">AC is:&nbsp;<strong id="ac">
				<?php if(is_array($device4) and array_key_exists("ac",$device4)){echo($device4['ac']);}?>
			</strong></li>
			<li class="list-group-item">Windows is:&nbsp;<strong id="window">
				<?php if(is_array($device4) and array_key_exists("window",$device4)){echo($device4['window']);}?>
			</strong></li>
			<li class="list-group-item">RainDrops:&nbsp;<strong id="rainDrops">
				<?php if(is_array($device4) and array_key_exists("rainy",$device4)){echo($device4['rainy']);}?>
			</strong></li>
			<li class="list-group-item">Last Updated:<strong id="lastUpdatedDevice4">
				<?php if(is_array($device4) and array_key_exists("date",$device4)){echo($device4['date']);}?>
			</strong></li>
			
		</ul>
		
		
		<div class="footer-buttons">
			<button class="btn btn-danger control btn-sm controlButton" value="lighton" id="lightOnDevice4">Light On</button>
			<button class="btn btn-danger control btn-sm controlButton" value="acon" id="acOn">AC On</button>
			<button class="btn btn-danger control btn-sm controlButton" value="lightoff" id="lightOffDevice4">Light Off</button>
			<button class="btn btn-danger control btn-sm controlButton" value="acoff" id="acOff">AC Off</button>
		</div>
		
	</div>	
	
	<div style="clear: both;"></div>
	
	
	<div class="card device" id="alldevices">
									<!---Corridor Device(Relay for now)-->
		<div class="card-block card-header">
			<h4 class="card-title">Devices Control</h4>
		</div>
		<img class="card-img-top cardImage" src="images/lighton.png" alt="Card image cap"><br>
		<ul class="list-group list-group-flush" id="deviceall">
			<li class="list-group-item">
					<button class="btn btn-primary control controlAll btn" value="turnOnAll" id="lightOnAll">All Lights On</button>
			</li>
				<li class="list-group-item">
					<button class="btn btn-primary control controlALl btn " value="turnOffAll" id="lightOffAll">All Lights Off</button>
			</li>
			
				<li class="list-group-item">
					<button class="btn btn-primary control controlAll btn " value="turnOffDevices" id="deviceOffAll">All Devices Off</button>
			</li>
		</ul>
	</div>	
	
	
	
	
	
</div>


	<script type="text/javascript" src="scripts/jquery.min.js"></script>
	<script src="scripts/tether-master/dist/js/tether.min.js"></script>
	<script src="scripts/bootstrap/js/bootstrap.min.js"></script>


	<script type="text/javascript">
	
		
	$("#home").removeClass("active");
	$("#features").addClass("active");
	changeData();	
		
	function disableAll(){
		var buttons = $("button");
		for(i =0 ; i < buttons.length ;i++){
			
			$(buttons[i]).prop('disabled', true);
		}
	}	
	
	function changeData(){
		var statusButtons = document.getElementsByClassName("status");
		
		for (i=0;i< statusButtons.length;i++){
			$(statusButtons[i]).prop('disabled',false);
	}
		var allDevices = document.getElementsByClassName("controlAll");
		
		for(i=0; i < allDevices.length ; i++){
			$(allDevices[i]).prop('disabled',false);
		}
		
		var lightElements = document.getElementsByClassName("light");
		for(i=0; i< lightElements.length ; i++){
			var lightStatus = lightElements[i].innerText;
			var str = lightElements[i].id.split("Device");
			//console.log("Inner html: " + lightStatus);
			//console.log("for device: "+str);
			if(lightStatus == "on" ){
				var device = "#lightOnDevice" + str[1];
				$(device).prop('disabled', true);	
				$("#lightOffDevice" + str[1]).prop('disabled', false);
			}else if(lightStatus =="off" ){
				var device = "#lightOffDevice" + str[1];
				$(device).prop('disabled', true);
				$("#lightOnDevice" + str[1]).prop('disabled', false);
			}
		}
		
		
		var security =document.getElementById("homeSecurity");//$("#homeSecurity");
		var tv = document.getElementById("tv");//$("#tv");
		var ac = document.getElementById("ac");//$("#ac");
		
		stat = security.innerText;
		//console.log(stat);
		if(stat =="secure"){
			$("#securityOn").prop('disabled', true);
			$("#securityOff").prop('disabled', false);
		} else if(stat.match("unsecure")){
			$("#securityOn").prop('disabled', false);
			$("#securityOff").prop('disabled', true);
		}
		stat = tv.innerText;
		//console.log("tv:"+stat);
		if(stat.match("on")){
			$("#tvOn").prop('disabled', true);
			$("#tvOff").prop('disabled', false);
		} else if(stat.match("off")){
			$("#tvOn").prop('disabled', false);
			$("#tvOff").prop('disabled', true);
		}
		stat = ac.innerText;
		//console.log("ac:"+ stat);
		if(stat.match("on")){
			$("#acOn").prop('disabled', true);
			$("#acOff").prop('disabled', false);
		} else if(stat.match("off")){
			$("#acOn").prop('disabled', false);
			$("#acOff").prop('disabled', true);
		}
		
	}	

		
	function updateData(response,device){
		//disableAll();
				
		if(device == 1){
			
			var temprature = response.temprature;
			var humidity = response.humidity;
			var time = response.date;
			//console.log("Temprature: "+temprature);
			$("#temprature").html(temprature);
			$("#humidity").html(humidity);
			$("#lastUpdatedDevice1").html(time);
			changeData();
			
			
			
		} else if(device == 2){
			
			var lightStatus = response.light;
			var security = response.homesecuriety;
			var door = response.door;
			var time = response.date;
			//console.log(lightStatus);
			//console.log(security);
			//console.log(door);
			//console.log(time);
			$("#lightStatusDevice2").html(lightStatus);
			$("#doorStatus").html(door);
			$("#homeSecurity").html(security);
			$("#lastUpdatedDevice2").html(time);
			//After changing the html in light lets check this: In the span containing lightStatus
			changeData();
				
				
		} else if(device == 3){
			var lightStatus = response.light;
			var tv = response.tv;
			var date = response.date
			$("#lightStatusDevice3").html(lightStatus);
			$("#tv").html(tv);
			$("#lastUpdatedDevice3").html(date);
			changeData();
				
		
		} else if(device == 4){
			//console.log(response);
			var lightStatus = response.light;
			var ac = response.ac;
			var window = response.window;
			var rainy = response.rainy;
			var time = response .date;
			$("#lightStatusDevice4").html(lightStatus);
			$("#ac").html(ac);
			$("#window").html(window);
			$("#rainDrops").html(rainy);
			$("#lastUpdatedDevice4").html(time);
			//After changing the html in light lets check this: In the span containing lightStatus
			changeData();
		}

	}

	function getStatus(){
		var parent = this.parentElement;
		var xhr = new XMLHttpRequest();
		
		url = "script.php";
		url += "?device=" + parent.id; //Pass the device is
		xhr.open("GET",url,true);
		xhr.setRequestHeader("X-Requested-With","AJAX");
		disableAll();
		xhr.onreadystatechange = function(){
			if(xhr.readyState == 4 && xhr.status == 200) {
				var messageAlert = document.getElementById("message");
				var response = JSON.parse(xhr.responseText);
				//var response = xhr.responseText;
				console.log(response);
				
				if(parent.id =="device1"){
					updateData(response,1);
				}
				else if(parent.id =="device2"){
					updateData(response,2);
				} else if(parent.id =="device3"){
					updateData(response,3);
				}else if(parent.id == "device4"){
					updateData(response,4);
				}

			}
		};

		xhr.send();

	}
	function postData(){
		var parent = this.parentElement;
		var id = parent.parentElement.id;
		var xhr = new XMLHttpRequest();
		url = "script.php";
		xhr.open("POST",url,true);
		xhr.setRequestHeader("Content-type","application/x-www-form-urlencoded");
		xhr.setRequestHeader("X-Requested-With","AJAX");
		$("#message").html("Sending Data please wait");
		disableAll();
		
		xhr.onreadystatechange = function(){
			if(xhr.readyState == 4 && xhr.status == 200) {
				var messageAlert = document.getElementById("message");
				if(id == "deviceall"){
					window.location.reload();
					return;
				}
				var response = JSON.parse(xhr.responseText);
				$("#message").html("");
				//var response = (xhr.responseText);
				//console.log(response);
				
				//$("#message").html(response);
				//Becuase after sending data we need to update status
				
				if(id =="device1"){
					updateData(response,1);
				}
				
				else if(id =="device2"){
					updateData(response,2);
				}
				else if(id =="device3"){
					updateData(response,3);
				}
				else if(id =="device4"){
					updateData(response,4);
				}
				
		
			}
		};

		xhr.send("device="+id +"&value="+this.value +"&id="+this.id);

	}


	
	

	
	var statusButtons = document.getElementsByClassName("status");
	var controlButtons = document.getElementsByClassName("control");

	for (i=0;i< statusButtons.length;i++){

		statusButtons[i].addEventListener("click",getStatus);
	}


	for (i=0;i< controlButtons.length;i++){

		controlButtons[i].addEventListener("click",postData);
	}
		
		
	
	
		

	</script>
