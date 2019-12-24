<?php
/*
	session_start();
	$link = mysqli_connect("localhost","raspberry","helloworld","raspberry");
	$user = "";

	if(array_key_exists("id",$_COOKIE) and $_COOKIE["id"] != ""){
		$_SESSION['id'] = $_COOKIE['id'];
	}
	if(array_key_exists("id",$_SESSION) and $_SESSION["id"] != ""){
		$query ="select username from login where id='".mysqli_real_escape_string($link,$_SESSION['id'])."' limit 1";
		if($res = (mysqli_query($link,$query))){
			$row = mysqli_fetch_array($res);

			if (array_key_exists("username" ,$row)) {
				$user = $row['username'];

			}
		}
	} else{
		header("Location:index.php");
	}
*/


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
		#container-loading{
			background:#262626;
			text-align: center;
			color:white;
			display:none;
		}
		
	
	</style>
</head>

<body>

<?php include("items/navbar.php"); ?>







<?php include("items/jumptron.php");  ?>
<div class="container-fluid" id="homePage">

	
	<h1>Welcome to the home page</h1>
</div>



<div class="container-fluid" id="container-loading">
	<img src="images/loading.gif">
	<p>Please wait... getting data</p>
</div>

<div class="alert" id="msg" alert></div>


<script type="text/javascript" src="scripts/jquery.min.js"></script>
<script src="https://npmcdn.com/tether@1.2.4/dist/js/tether.min.js"></script>
<script src="scripts/bootstrap/js/bootstrap.min.js"></script>


<script type="text/javascript">
		
	var featuresDisabled = false;
	
	$("#home").addClass("active");
	$("#features").removeClass("active");
	
	function waitForData(button){
		$("#features").addClass("disabled");
		$("#homePage").hide();
		$("#container-loading").show();
	}
	
		
	function gotData(){
		$("#homePage").show();
		$("#container-loading").hide();
		
	}
	//Ajax to work behind the scenes to get the data and store them in a session	
	function updateFeaturesData(){
		if(!featuresDisabled){
			
		waitForData(this);
		var xhr = new XMLHttpRequest();
		url = "phpscripts/getdata.php";
		xhr.open("GET",url,true);
		xhr.setRequestHeader("X-Requested-With","AJAX");
		xhr.onreadystatechange = function(){
			if(xhr.readyState == 4 && xhr.status == 200) {
				gotData();
				featuresDisabled = false;
				var response = xhr.responseText
				if(response != ""){
					$("#msg").html(response);
				}else {
					window.location.href = "TrialRun.php";
				}
			
				
				
			}
		};
			
		xhr.send();	
		}
		
		
	}	
	
	document.getElementById("features").addEventListener("click",updateFeaturesData);
</script>
