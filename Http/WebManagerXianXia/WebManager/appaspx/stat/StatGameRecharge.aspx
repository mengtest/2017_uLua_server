﻿<%@ Page Title="" Language="C#" MasterPageFile="~/appaspx/stat/StatCommon.master" AutoEventWireup="true" CodeBehind="StatGameRecharge.aspx.cs" Inherits="WebManager.appaspx.stat.StatGameRecharge" %>
<asp:Content ID="Content1" ContentPlaceHolderID="stat_comm_HeadContent" runat="server">
   <%-- <script type="text/javascript" src="/Scripts/DateRange/js/jquery-1.3.1.min.js"></script> --%>
	<script type="text/javascript" src="/Scripts/DateRange/js/jquery-ui-1.7.1.custom.min.js"></script>
	<script type="text/javascript" src="/Scripts/DateRange/js/daterangepicker.jQuery.js"></script>
	<link rel="stylesheet" href="/Scripts/DateRange/css/ui.daterangepicker.css" type="text/css" />
	<link rel="stylesheet" href="/Scripts/DateRange/css/redmond/jquery-ui-1.7.1.custom.css" type="text/css" title="ui-theme" />
	<script type="text/javascript">
	    $(document).ready(function ()
	    {
	        $('#MainContent_stat_common_m_time').daterangepicker({ arrows: false });
	    });
	</script>
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="stat_common" runat="server">
    <h2>游戏每天收入统计</h2>
    时间区间:<asp:TextBox ID="m_time" runat="server" style="width:300px;"></asp:TextBox>
    <asp:Button ID="Button3" runat="server" onclick="onStat" Text="统计" style="width:60px;height:30px" />

    <asp:Table ID="m_result" runat="server" CssClass="result">
    </asp:Table>
</asp:Content>
