<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must provide your confirmation password.");
        }
        else if (($_POST["password"]) != ($_POST["confirmation"]))
        {
            apologize("Passwords do not match.");
        }
        // check if username already exists
        else if ( query("SELECT * from users WHERE username = ?", $_POST["username"]) != false)
        {
            apologize("Username already exist. Choose another name.");
        }
        else
        {
            $result = query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"]));
            if (result !== false)
            {
                $rows = query("SELECT LAST_INSERT_ID() AS id");
                $id = $rows[0]["id"];
                $_SESSION["id"];
                redirect("/");
            }
            else
            {
                apologize("Sorry, couldn't create new user.");
            }
        }
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

?>
