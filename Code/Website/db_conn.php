$sname= "sql301.infinityfree.com";
$unmae= "if0_35139378";
$password = "6K3JtNhvbsgz";
$db_name = "if0_35139378_database";
$conn = mysqli_connect($sname, $unmae, $password, $db_name);
if (!$conn) {
    echo "Connection failed!";
}