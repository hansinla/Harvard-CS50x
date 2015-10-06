<style>
#stocktable
{
    font-family:"Trebuchet MS", Arial, Helvetica, sans-serif;
    width:60%;
    border-collapse:collapse;
    margin-left: auto;
    margin-right: auto;
}
#stocktable td, #stocktable th 
{
    font-size:1em;
    text-align:left;
    border:1px solid #A0A0A0;
    padding:3px 7px 2px 7px;
}
#stocktable th 
{
    font-size:1.1em;
    text-align:center;
    padding-top:5px;
    padding-bottom:4px;
    background-color:#A0A0A0;
    color:#ffffff;
}
#stocktable tr
{
    background-color:#E5E5E5;
}
#stocktable tr td.alt
{
    text-align:right;
}
</style>

<table id="stocktable">
<tr>
    <th>Name</th>
    <th>Symbol</th>
    <th>Number</th>		
    <th>Price</th>
    <th>Total</th>
</tr>

<?php foreach ($positions as $position): ?>
    
    <tr>
        <td><?= $position["name"] ?></td>
        <td><?= $position["symbol"] ?></td>
        <td class="alt"><?= $position["shares"] ?></td>
        <td class="alt"><?= $position["price"] ?></td>
        <td class="alt"><?= number_format($position["price"] * $position["shares"], 2) ?></td>
    </tr>

<?php endforeach ?>

</table>
<b>
        Cash position: $<?= $cash ?>
</b>
<br/>
<br/>
<div>
    <a href="logout.php">Log Out</a>
</div>
