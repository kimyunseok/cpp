<%@page import="java.io.File"%>
<%@page import="java.util.Enumeration"%>
<%@page import="com.oreilly.servlet.multipart.DefaultFileRenamePolicy"%>
<%@page import="com.oreilly.servlet.MultipartRequest"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC"-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
 
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>업로드</title>
<script>
function autoSubmit() {
	 document.getElementById("productSubmit").click(); // Simulates button click
     document.productForm.submit();
}
</script>
</head>
 
<%
    // request.getRealPath("상대경로") 를 통해 파일을 저장할 절대 경로를 구해온다.
    // 운영체제 및 프로젝트가 위치할 환경에 따라 경로가 다르기 때문에 아래처럼 구해오는게 좋음
    String uploadPath = application.getRealPath("\\image\\product");

    int maxSize =1024 *1024 *10;// 한번에 올릴 수 있는 파일 용량 : 10M로 제한
     
    String fileName ="";
    
    MultipartRequest multi = null;
     
    try{
        // request,파일저장경로,용량,인코딩타입,중복파일명에 대한 기본 정책
        multi = new MultipartRequest(request,uploadPath,maxSize,"utf-8");
        
        // 전송한 전체 파일이름들을 가져옴
        Enumeration files = multi.getFileNames();
         
        if(files.hasMoreElements()){
            // form 태그에서 <input type="file" name="여기에 지정한 이름" />을 가져온다.
            String file1 = (String)files.nextElement();// 파일 input에 지정한 이름을 가져옴
            // 그에 해당하는 실재 파일 이름을 가져옴
            fileName = multi.getOriginalFileName(file1);
        }
    }catch(Exception e){
        e.printStackTrace();
    }
    if(fileName == "") {
    	fileName = multi.getParameter("img");
    } else {
    	fileName = "image\\product\\" + fileName;
    }
%>
<body onload="setTimeout('autoSubmit()', 1000)">
<center>
			<form action="ProductController" method="post" id="productForm" name="productForm">
			<table width="800">
					<span style="font-size: 45px; font-family: sans-serif;"><b><br><br>상품 준비완료</b></span>
					<span style="font-size: 30px; font-family: sans-serif;"><b><br><br>상품의 추가 / 수정이 완료되었습니다.</b></span>
					<span style="font-size: 20px; font-family: sans-serif;"><b><br><br>페이지가 자동으로 새로고침 됩니다.</b></span>
			</table><br><br>
			<table width="700" heigh="600" cellpadding="0"
				style="border-collapse: collapse; font-size: 16px; visibility: collapse;">
				<tr class="addProduct" hegiht="30">
					<td width="5%" align="center"> </td>
					<td width="15%">제품 인덱스</td>
					<td><input type="text" id="productidx" name="productidx" 
					value="<%=multi.getParameter("productidx") == null ? "" : multi.getParameter("productidx")%>"/>
					</td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class="addProduct" hegiht="30">
					<td width="5%" align="center"> </td>
					<td width="15%">제품 타입</td>
					<td><input type="text" size="2" id="producttype" name="producttype" maxlength="2"
					value="<%= multi.getParameter("producttype")%>"/>
					</td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=addProduct " height="30">
					<td width="5%" align="center">*</td>
					<td width="15%">제품 이름</td>
					<td><input type="text" name="productname" id="productname" maxlength="25"
					value="<%=multi.getParameter("productname")%>"/></td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=addProduct " height="30">
					<td width="5%" align="center"> </td>
					<td width="15%">이미지</td>
					<td><input type="text" name="img" id="img"
					value="<%= fileName %>"/>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=addProduct " height="30">
					<td width="5%" align="center">*</td>
					<td width="15%">설명</td>
					<td><textarea name="explanation" id="explanation" style="width: 450px; height: 150px;"><%= multi.getParameter("explanation")%></textarea></td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=addProduct " height="30">
					<td width="5%" align="center">*</td>
					<td width="15%">가격</td>
					<td><input type="text" name="price" id="price" maxlength="9"
					value="<%= multi.getParameter("price")%>"/></td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=addProduct " height="30">
					<td width="5%" align="center">*</td>
					<td width="15%">수량</td>
					<td><input type="text" name="qty" id="qty" maxlength="4"
					value="<%= multi.getParameter("qty")%>"/></td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr height="40">
					<td><input width="120" type="submit" value="상품추가" id="productSubmit" style="border-radius: 5px; background-color: black; color: white;"/>&nbsp;</td>
				</tr>
			</table>
		</form>
		</center>
</body>