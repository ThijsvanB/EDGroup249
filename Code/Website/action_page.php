session_start(); 
<!DOCTYPE html>
<html>
<header>
</header>
<body>
        <?php

        echo "Hello\n\n";

        echo gethostbyname("sql301.epizy.com");
        echo "\n\n";
        var_export (dns_get_record ( "sql301.epizy.com" ) );

        $sname= gethostbyname("sql301.epizy.com");
        $unmae= "if0_35139378";
        $password = "6K3JtNhvbsgz";
        $db_name = "if0_35139378_database";
        $conn = mysqli_connect($sname, $unmae, $password, $db_name);
        if (!$conn) {
            echo "Connection failed!";
            ?>
            <?php if (!$conn) : ?>
                <a>kut momentje</a>
            <?php endif; ?>
            <?php
            exit();
        }
        else {
            ?>
            <?php if (!$conn) : ?>
                <a>pog momentje</a>
            <?php endif; ?>
            <?php
        }

        if (isset($_POST['uname']) && isset($_POST['psw'])) {
            function validate($data){
                $data = trim($data);
                $data = stripslashes($data);
                $data = htmlspecialchars($data);
                return $data;
            }

            $uname = validate($_POST['uname']);
            $pass = validate($_POST['psw']);

            if (empty($uname)) {
                header("Location: index.php?error=juname is required");
                exit();
            }else if(empty($pass)){
                header("Location: index.php?error=Password is required");
                exit();
            }else{
                $sql = "SELECT * FROM accounts WHERE user_name='$uname' AND password='$pass'";
                $result = mysqli_query($conn, $sql);

                if (mysqli_num_rows($result) === 1) {
                    $row = mysqli_fetch_assoc($result);

                    if ($row['user_name'] === $uname && $row['password'] === $pass) {
                        $_SESSION['user_name'] = $row['user_name'];
                        $_SESSION['name'] = $row['name'];
                        $_SESSION['id'] = $row['id'];

                        header("Location: action_page.php");
                        exit();
                    }else{
                        header("Location: action_page.php?error=Incorect User name or password");
                        exit();
                    }
                }else{
                    exit();
                }
            }
        }else{
            header("Location: action_page.php");
            exit();
        }
        ?>
</body>
</html>