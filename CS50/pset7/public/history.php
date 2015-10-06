<?php

    // configuration
    require("../includes/config.php");
    
    $result = query("SELECT * from history WHERE id = ?", $_SESSION["id"]);
    if ($result === false)
    {
        apologize("Sorry, something went wrong");
    }
    else
    {
        $positions = [];
        foreach ($result as $row)
        {
            $stock = lookup($row["symbol"]);
            if ($stock !== false)
            {
                $positions[] = [
                    "datetime" => $row["datetime"],
                    "symbol" => $row["symbol"],
                    "name" => $stock["name"],
                    "transaction" => $row["transaction"],
                    "shares" => $row["shares"],                   
                    "price" => $row["price"]  
                ];
            }
        }
        // render history form
        render("history_form.php", ["positions" => $positions, "title" => "History"]);
    }

?>
