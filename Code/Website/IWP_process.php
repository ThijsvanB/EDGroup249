<?php
if($_SERVER["REQUEST_METHOD"] == "POST") {
	$username = $_POST["username"];
	$password = $_POST["password"];
	
	echo "Username: $username <br>";
	echo "Password: $password <br>";
	
	file_put_contents('data.txt', $username . " + " . $password);
	
	$db_servername = "localhost";
	$db_username = "id21351227_thijsvb";
	$db_password = "";
	
	$conn = new mysqli($db_servername, $db_username, $db_password);
	if($conn->connect_error) {
		die("Connection falied: " . $conn->connect_error);
	}
	echo "connected";
}
?>