﻿<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="GmInfoViewTree.aspx.cs" Inherits="WebManager.appaspx.account.GmInfoViewTree" %>
<asp:Content ID="Content1" ContentPlaceHolderID="HeadContent" runat="server">
    <script src="../../Scripts/module/sea.js"></script>
    <script type="text/javascript">
        seajs.use("../../Scripts/account/AccountProperty.js");
	</script>
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <div  class="cSafeWidth">
        <span id="m_creator" style="font-size:medium;color:black;font-weight:bold" runat="server"></span>
    </div>
    <div class="container-fluid">
        <asp:Table ID="m_result" runat="server" CssClass="table table-hover table-bordered">
        </asp:Table>
    </div>
    <div id="divModifyName" class="PopDialog">
        <div class="container form-horizontal PopDialogBg">
            <h2 style="text-align:center;padding:10px;margin-bottom:10px;background:#ccc;cursor:pointer;" class="close">关闭</h2>
            <h3 style="text-align:center;padding:10px;margin-bottom:10px;">修改别名</h3>
            <div class="form-group">
                <label for="account" class="col-sm-2 control-label">账号:</label>
                <div class="col-sm-10">
                    <input type="text" class="form-control" id="txtAccount" disabled="disabled" /> 
                </div>
            </div> 
            <div class="form-group">
                <label for="account" class="col-sm-2 control-label">别名:</label>
                <div class="col-sm-10">
                    <input type="text" class="form-control" id="txtNewName" /> 
                </div>
            </div> 
            <div class="form-group">
                <div class="col-sm-offset-2 col-sm-10">
                        <input type="button" value="提交修改" class="btn btn-primary form-control" id="btnModifyName" />
                </div>
            </div>
            <div class="form-group">
                <div class="col-sm-offset-2 col-sm-10">
                    <span id="opRes" />
                </div>
            </div>
        </div>
    </div>
</asp:Content>
