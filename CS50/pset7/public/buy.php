<?php
    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]) || empty($_POST["number"]))
        {
            apologize("You must provide a stock symbol and number of shares to buy.");
        }
        else if (preg_match("/^\d+$/", $_POST["number"]) === false)
        {
            apologize("Please enter a positive whole number of shares.");
        }
        else 
        {
            // check for valid stock
            $stock = lookup($_POST["symbol"]);
        }
        if ($stock === false)
        {
            apologize("I can't find that stock.");
        }
        else
        {   
            // Calculate how much this transaction would cost
            $totalvalue = $_POST["number"] * $stock["price"];
            // Find how much cash the user has
            $cashholding = query("SELECT cash from users WHERE id = ?", $_SESSION["id"]);
            $cash = $cashholding[0]["cash"];
            if ($totalvalue > $cash)
            {
                apologize("Sorry, you don't have enough money.");
            }
            else
            {
                // valid purchase, update stock
                query("INSERT INTO stock(id, symbol, shares) VALUES(?, ?, ?)
                        ON DUPLICATE KEY UPDATE shares = shares + ?",
                        $_SESSION["id"], $stock["symbol"], $_POST["number"], $_POST["number"]);
                // Now let the user pay for the purchase, update users
                query("UPDATE users SET cash = cash - ? WHERE id = ?", $totalvalue, $_SESSION["id"]);
                
                // update history
                query("INSERT INTO history(id, symbol, transaction, shares, price) VALUES(?, ?, ?, ?, ?)", 
                        $_SESSION["id"], $stock["symbol"], "BUY", $_POST["number"], $stock["price"]);
                        
                 // get time stamp
                $rows = query("SELECT datetime FROM history ORDER BY datetime DESC LIMIT 1");
                $datetime = $rows[0]["datetime"];
                            
                // send email
                sendmail($datetime, $stock["symbol"], $stock["name"], "BUY", $stock["price"]);
            }
            // redirect to portfolio
            redirect("/");
        }
    }
    else
    {
        // else render form
        render("buy_form.php", ["title" => "Buy"]);
    }
?>
