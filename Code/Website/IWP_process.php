<?php
if($_SERVER["REQUEST_METHOD"] == "POST") {
	$device_id = $_POST["device_id"];
	$sensor_value = $_POST["sensor_value"];
	
	file_put_contents('data.txt', $device_id . " + " . $sensor_value);
	
	$db_servername = "localhost";
	$db_username = "id21351227_thijsvb";
	$db_password = "tHijS78@";
	
	$conn = new mysqli($db_servername, $db_username, $db_password);
	if($conn->connect_error) {
		die("Connection falied: " . $conn->connect_error);
	}
	echo "connected";
	
	$conn->query("USE id21351227_users");
	
	$sql = "UPDATE users SET sensor_value = " . $sensor_value . " WHERE device_id = " . $device_id . ";";
	if($conn->query($sql) === TRUE) {
		echo "Record updated successfully";
	} else {
		echo "Error updating record: " . $conn->error;
	}
	
	$conn->close();
}
?>