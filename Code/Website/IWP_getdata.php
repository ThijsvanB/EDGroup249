<!DOCTYPE html>
<html>

<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width">
	<title>IWaterPlant</title>
	<link href="IWPstyle.css" rel="stylesheet" type="text/css">
</head>

<body>
	<div class="background">
		<div class="blur">
			<script src="IWPscript.js"></script>
			
			<ul>
				<li class="Navigation"><a href="index.html">Home</a></li>
				<li class="Navigation"><a href="IWP_about.html">About</a></li>
				<li class="Navigation"><a href="IWP_your_plant.html">Your plant</a></li>
			</ul> 

			<div id="Introduction">
				<h1>4WBB0 - Engineering design - group 249 - IWaterPlant</h1>
			</div>
			
			<div>
				<?php
					$deviceId = $_POST["deviceId"];
				
					$db_servername = "localhost";
					$db_username = "id21351227_thijsvb";
					$db_password = "";
					
					$conn = new mysqli($db_servername, $db_username, $db_password);
					if($conn->connect_error) {
						die("Connection to database failed, try again. Error code: " . $conn->connect_error);
					}
					
					$conn->query("USE id21351227_users");
					
					$sql = "SELECT sensor_value FROM users WHERE device_id = $deviceId";
					$result = $conn->query($sql);
					if($result->num_rows == 0) {
						die("Not a registered device id");
					}
					
					echo "value: " . ($result->fetch_assoc())["sensor_value"] . "<br>";
				?>
			</div>
		</div>
	</div>
</body>

</html>