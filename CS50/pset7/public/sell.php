<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a stock symbol.");
        }
        else 
        {
            $result = query("SELECT * FROM stock WHERE symbol = ? AND id = ?", $_POST["symbol"], $_SESSION["id"]);
        }
        
        if ($result === false)
        {
            apologize("You don't own that stock.");
        }
        else
        {
            $shares = $result[0]["shares"];
            $stock = lookup($_POST["symbol"]);
            $totalvalue = $shares * $stock["price"];
            query("UPDATE users SET cash = cash + ? WHERE id = ?", $totalvalue, $_SESSION["id"]  );
            query("DELETE FROM stock WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
            
            // update history
           query("INSERT INTO history(id, symbol, transaction, shares, price) VALUES(?, ?, ?, ?, ?)",
                        $_SESSION["id"], $stock["symbol"], "SELL", $shares, $stock["price"]);
                        
            // get time stamp
            $rows = query("SELECT datetime FROM history ORDER BY datetime DESC LIMIT 1");
            $datetime = $rows[0]["datetime"];
                        
            // send email
            sendmail($datetime, $stock["symbol"], $stock["name"], "SELL", $stock["price"]);

            // redirect to portfolio
            redirect("/");
        }
    }
    else
    {
        // else render form
        render("sell_form.php", ["title" => "Sell"]);
    }

?>
