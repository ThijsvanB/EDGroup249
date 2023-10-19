<?php
if($_SERVER["REQUEST_METHOD"] == "GET") {
	$device_id = $_GET["device_id"];
	
	$db_servername = "localhost";
	$db_username = "id21351227_thijsvb";
	$db_password = "tHijS78@";
	
	$conn = new mysqli($db_servername, $db_username, $db_password);
	if($conn->connect_error) {
		die("Connection falied: " . $conn->connect_error);
	}
	
	$conn->query("USE id21351227_users");
	
	$sql = "SELECT depth_water_requirement FROM users WHERE device_id = " . $device_id . ";";
	$result = $conn->query($sql);
	if($result->num_rows == 1) {
		echo $result->fetch_assoc()["depth_water_requirement"];
	} else {
		echo "-1";
	}
	
	$conn->close();
}
?>