<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>

<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt"%>
<!DOCTYPE html>
<html>
<head>
	<title>장바구니</title>
	<link type="text/css" rel="stylesheet" href="style.css?">

</head>
<body>
	<header>
		<%@include file="layout/header.jsp"%>
	</header>
		<%@ include file="layout/menubar.html"%>
	<aside class="product">
		<center>
		<h1>내 장바구니 확인</h1>
		<table class="table" cellpadding="10" width="80%">
			<tr>
                <th style="text-align: center">이미지</th>
                <th style="text-align: center">제품 이름</th>
                <th style="text-align: center">스펙</th>
                <th style="text-align: center">가격</th>
                <th style="text-align: center">수량</th>
                <th></th>
            </tr>
			<tr>				
			<c:forEach items="${products}" var="product" varStatus="status">
                <tr>
                    <td width="15%" style="border-right: 1px solid #C1C1C1; border-left: 1px solid #C1C1C1;"><img src="<c:out value="${product.img}"/>" style="width: 200px; height: 200px;"></td>
                    <td width="10%" style="word-break:break-all; border-right: 1px solid #C1C1C1;"><a href="ProductController?action=detail&productidx=<c:out value="${product.productidx}"/>"><c:out value="${product.productname}" /></a></td>
                    <td width="30%" style="word-break:break-all; border-right: 1px solid #C1C1C1;"><pre><c:out value="${product.explanation}" /></pre></td>
                    <td width="15%" style="word-break:break-all; border-right: 1px solid #C1C1C1;"><fmt:formatNumber value="${product.price}" pattern="#,###" ></fmt:formatNumber>&nbsp;원</td>
                    <td width="10%" style="word-break:break-all; border-right: 1px solid #C1C1C1;"><c:out value="${baskets[status.index].qty} 개"/></td>
                    
                    <td width="10%" style="background: blue;"><a style="color: white; font-size: 20px;" 
                    href="BasketController?action=order&productidx=${product.productidx}&qty=${baskets[status.index].qty}"><b>주문하기</b></a></td>
                    
                    <td width="10%" style="background: red;"><a style="color: white; font-size: 20px;" 
                    href="BasketController?action=delete&basketidx=<c:out value="${baskets[status.index].basketidx}"/>"><b>삭제</b></a></td>
            </c:forEach>
			</tr>
		</table>
		</center>
	</aside>
	<footer>
		<%@include file="layout/bottom.jsp"%>
	</footer>
</html>