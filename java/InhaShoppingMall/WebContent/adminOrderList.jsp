<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
    
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt"%>
<!DOCTYPE html>
<html>
<head>
	<title>관리자 주문내역 확인</title>
	<link type="text/css" rel="stylesheet" href="style.css?">

</head>
<body>
	<aside class="product">
		<center>
		<h1>관리자 주문내역 확인</h1>   
    
    	<input type="button" onclick="location.href='index.jsp'" value="홈화면" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; margin-right: 30px; font-size: 18px;"/>
     </p>
		<table cellpadding="10"
				style="border-collapse: collapse; font-size: 16px;" border="5">
			<thead style="background: black; color: white;">
			<tr>
				<th style="text-align: center">IDX</th>
				<th style="text-align: center">주문자</th>
                <th style="text-align: center">이미지</th>
                <th style="text-align: center">제품 이름</th>
                <th style="text-align: center">스펙</th>
                <th style="text-align: center">가격</th>
                <th style="text-align: center">수량</th>
                <th style="text-align: center">메모</th>
                <th></th>
            </tr>
            </thead>
			<tr>				
			<c:forEach items="${products}" var="product" varStatus="status">
                <tr>
                    <td width="10%" style="word-break:break-all; border-right: 1px solid #C1C1C1;"><c:out value="${orders[status.index].orderidx}"/></td>
                    <td width="10%" style="word-break:break-all; border-right: 1px solid #C1C1C1;"><c:out value="${orders[status.index].userid}"/></td>
                    <td width="10%" style="border-right: 1px solid #C1C1C1; border-left: 1px solid #C1C1C1;"><img src="<c:out value="${product.img}"/>" style="width: 200px; height: 200px;"></td>
                    <td width="10%" style="word-break:break-all; border-right: 1px solid #C1C1C1;"><a href="ProductController?action=detail&productidx=<c:out value="${product.productidx}"/>"><c:out value="${product.productname}" /></a></td>
                    <td width="15%" style="word-break:break-all; border-right: 1px solid #C1C1C1;"><pre><c:out value="${product.explanation}" /></pre></td>
                    <td width="10%" style="word-break:break-all; border-right: 1px solid #C1C1C1;"><fmt:formatNumber value="${product.price}" pattern="#,###" ></fmt:formatNumber>&nbsp;원</td>
                    <td width="10%" style="word-break:break-all; border-right: 1px solid #C1C1C1;"><c:out value="${orders[status.index].qty} 개"/></td>
                    <td width="15%" style="word-break:break-all; border-right: 1px solid #C1C1C1;"><pre><c:out value="${orders[status.index].memo}"/></pre></td>
                    <td width="10%" style="background: red; text-align: center; font-size: 30px;"><a style="color: white" href="OrderController?action=delete&orderidx=<c:out value="${orders[status.index].orderidx}"/>">삭제</a></td>
            </c:forEach>
			</tr>
		</table>
		</center>
	</aside>
</html>