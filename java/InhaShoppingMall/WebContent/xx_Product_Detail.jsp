<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>

<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt"%>
<!DOCTYPE html>
<html>
<head>
	<jsp:useBean id = "product" class="com.inhamall.model.Product" scope="request"></jsp:useBean>
	<jsp:setProperty property="*" name="product"/>
	<title><jsp:getProperty property="productname" name="product"/></title>
	<link type="text/css" rel="stylesheet" href="style.css?">
	<script>
	function order(){
		<%if(session.getAttribute("id") == null) {%>
		alert("로그인을 해야 주문할 수 있습니다.");
		return false;
		<%}%>
	}
	
	function basketAdd() {
		var pdfrm = document.productForm;
		<%if(session.getAttribute("id") == null) {%>
		alert("로그인을 해야 장바구니 기능을 사용할 수 있습니다.");
		return false;
		<%} else {%>
		alert("장바구니에 담기가 완료됐습니다.");
		<%} %>
		pdfrm.action="BasketController"
		pdfrm.submit();
	}
	</script>
</head>
<body>
	<header>
		<%@include file="layout/header.jsp"%>
	</header>
		<%@ include file="layout/menubar.html"%>
		<center>
		<form name="productForm" method="post" action="order.jsp" onsubmit="return order()">
			<table class="table">
		<tr>
			<td width="40%" rowspan="6"	 style="padding-right: 100px;"><img src="<jsp:getProperty property="img" name="product"/>" style="width: 500px; height: 500px;"></td>
			<td width="30%" style="word-break:break-all; border-bottom: 1px solid #C1C1C1;"><h1><jsp:getProperty property="productname" name="product"/></h1></td>
			<td width="30%"></td>
		</tr>
		<tr>
			<td style="word-break:break-all; border-bottom: 1px solid #C1C1C1;"><h3><fmt:formatNumber pattern="#,###" ><jsp:getProperty property="price" name="product"/></fmt:formatNumber>&nbsp;원</h3></td>
		</tr>
		<tr>
			<td style="word-break:break-all; border-bottom: 1px solid #C1C1C1;"><pre><jsp:getProperty property="explanation" name="product"/></pre></td>
		</tr>
		<tr>
			<td style="word-break:break-all; border-bottom: 1px solid #C1C1C1; padding-bottom: 15px;">재고 : <jsp:getProperty property="qty" name="product"/>&nbsp;개</td>
		</tr>
		<tr>
			<td style="border-bottom: 1px solid #C1C1C1; padding-bottom: 10px;"><select name="qty" id="qty" >
			<%for(int i = 1; i <= 10; i++) { %> 
			<option value="<%=i%>"><%=i+"개"%></option>
			<%} %>
			</select>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			
			<input type="submit" value="주문하기" style="background: black; color: white; width: 100px; height: 50px;"/>
			
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
			
			<input type="button" value="장바구니 담기" onclick="basketAdd()" style="background: black; color: white; width: 100px; height: 50px;"/> 
			
			<td style="visibility:collapse;"><input type="text" id="productidx" name="productidx" 
			value="<jsp:getProperty property="productidx" name="product"/>"/></td>
			<td style="visibility:collapse;"><input type="text" id="userid" name="userid" 
			value="<%=(String)session.getAttribute("id")%>"/></td>
			</form>
			</td>
		</tr>
		<tr>
		<td><span style="color: red;">※ 인하몰의 모든 제품의 배송비는 무료입니다.</span></td>
		</tr>
	</table>
	</center>
	<footer>
		<%@include file="layout/bottom.jsp"%>
	</footer>
</body>
</html>