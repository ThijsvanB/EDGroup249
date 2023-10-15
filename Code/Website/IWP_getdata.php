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
				<h1>IWaterPlant device ID <?php echo $_POST["deviceId"]?></h1>
			</div>
			
			<div>
				<?php
					$deviceId = $_POST["deviceId"];
				
					$db_servername = "localhost";
					$db_username = "id21351227_thijsvb";
					$db_password = "tHijS78@";
					
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
					
					if(empty($result->fetch_assoc()["plant_name"])) {
						echo "You have not yet selected a plant <br>";
					} else {
						echo "Your plant is: " . ($result->fetch_assoc())["plant_name"] . "<br>";
						echo "<script type='text/javascript'>document.getElementById('Selection').style.display = 'none';</script>";
						echo "<script type='text/javascript'>document.getElementById('Result').style.display = 'none';</script>";
					}
				?>
			</div>
			
			<div>
				<?php
					$deviceId = $_POST["deviceId"];
				
					$db_servername = "localhost";
					$db_username = "id21351227_thijsvb";
					$db_password = "tHijS78@";
					
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
			
			<div id="Selection">
				<label for="plantname">What kind of plant do you have: </label>
				<input type="text" id="plantname" name="plantname"></input><br><br>
				<button type="button" id="submitPlant" name="submitPlant" onclick="submitPlant()">Submit</button><br><br>
				<p><span id="details"></span></p>
			</div>
			
			<div id="Result">
			</div>
		</div>
	</div>
</body>

</html>