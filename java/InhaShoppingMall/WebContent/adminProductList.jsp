<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">

<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>제품 리스트</title>
</head>
<body>
<center>
<h1>제품 리스트 페이지</h1>    

	<input type="button" onclick="location.href='adminAddProduct.jsp'" value="상품 추가" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; margin-right: 30px; font-size: 18px;"/>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    
    <input type="button" onclick="location.href='index.jsp'" value="홈화면" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; margin-right: 30px; font-size: 18px;"/>
     </p>
     <div style="font-size: 20px"><b>
	 1x : 컴퓨터 노트북, 2x : PC장치(모니터 키보드 마우스), 3x : PC 주장치, 4x : 게이밍 관련</p>
	 
	 11 : 노트북 / 12 : 맥(애플) / 13 : 데스크탑 / 14: 태블릿 PC<br>
	 21 : 모니터 / 22 : 마우스 / 23 : 키보드 / 24 : 스피커 / 25 : 헤드폰<br>
	 31 : CPU / 32 : 램 / 33 : 그래픽카드 / 34 : 하드<br>
	 41 : 게이밍 장비 / 42 : 게임 / 43 : 공유기 / 44 : 프린터 / 45 : 기타<br>
	 </b>
	</div>
	</p>
    <table cellpadding="10"
				style="border-collapse: collapse; font-size: 16px;" border="5">
        <thead style="background: black; color: white;">
            <tr>
                <th>Idx</th>
                <th>제품 타입</th>
                <th>제품 이름</th>
                <th>이미지</th>
                <th>설명</th>
                <th>가격</th>
                <th>재고</th>
                <th colspan=2>편집</th>
            </tr>
        </thead>
        <tbody>
            <c:forEach items="${products}" var="product">
                <tr>
                    <td><c:out value="${product.productidx}" /></td>
                    <td><c:out value="${product.producttype}" /></td>
                    <td><c:out value="${product.productname}" /></td>
                    <td><img src="<c:out value="${product.img}"/>" style="width: 100px; height: 100px;"></td>
                    <td><pre><c:out value="${product.explanation}" /></pre></td>
                    <td><fmt:formatNumber value="${product.price}" pattern="#,###" ></fmt:formatNumber>&nbsp;원</td>
                    <td><c:out value="${product.qty}" /></td>
                    <td style="background: blue;"><a style="color: white" href="ProductController?action=edit&productidx=<c:out value="${product.productidx}"/>">수정</a></td>
                    <td style="background: red;"><a style="color: white" href="ProductController?action=delete&productidx=<c:out value="${product.productidx}"/>">삭제</a></td>
                </tr>
            </c:forEach>
        </tbody>
    </table>
 </center>
</body>
</html>