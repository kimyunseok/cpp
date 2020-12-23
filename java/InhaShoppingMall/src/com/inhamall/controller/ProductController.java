package com.inhamall.controller;

import java.io.IOException;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.inhamall.dao.ProductDao;
import com.inhamall.model.Product;

@WebServlet("/ProductController")
public class ProductController extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static String EDIT = "adminUpdateProduct.jsp";
    private static String LIST_PRODUCT = "adminProductList.jsp";
    private static String MAIN = "admin.jsp";
    private static String TYPE_1X_LIST = "1x_ProductList.jsp";
    private static String TYPE_2X_LIST = "2x_ProductList.jsp";
    private static String TYPE_3X_LIST = "3x_ProductList.jsp";
    private static String TYPE_4X_LIST = "4x_ProductList.jsp";
    private static String DETAIL_PRODUCT = "xx_Product_Detail.jsp";
    
    private ProductDao dao;

    public ProductController() {
        super();
        dao = new ProductDao();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    	request.setCharacterEncoding("UTF-8");
    	response.setContentType("text/html;charset=UTF-8");
    	
        String forward="";
        String action = request.getParameter("action");
        
        if (action.equalsIgnoreCase("delete")){
            int productidx = Integer.parseInt(request.getParameter("productidx"));
			String dir = request.getSession().getServletContext().getRealPath("");
            dao.deleteProduct(productidx, dir);
            forward = LIST_PRODUCT;
            request.setAttribute("products", dao.getAllProducts()); 
            
        } else if (action.equalsIgnoreCase("edit")){
            forward = EDIT;
            int productidx = Integer.parseInt(request.getParameter("productidx"));
            Product product = dao.getProductByIdx(productidx);	
            request.setAttribute("product", product);
       
        } else if (action.equalsIgnoreCase("listProduct")){
            forward = LIST_PRODUCT;
            List<Product> products = dao.getAllProducts();
            request.setAttribute("products", products);
            
        } else if (action.equalsIgnoreCase("detail")){
            forward = DETAIL_PRODUCT;
            int productidx = Integer.parseInt(request.getParameter("productidx"));
            Product product = dao.getProductByIdx(productidx);	
            request.setAttribute("product", product);
            
        } else if (action.equalsIgnoreCase("1x_list")){
        	int producttype = Integer.parseInt(request.getParameter("producttype"));
        	forward = TYPE_1X_LIST;
            List<Product> products = dao.getProductsByType(producttype);
            request.setAttribute("products", products);
        }  else if (action.equalsIgnoreCase("2x_list")){
        	int producttype = Integer.parseInt(request.getParameter("producttype"));
        	forward = TYPE_2X_LIST;
            List<Product> products = dao.getProductsByType(producttype);
            request.setAttribute("products", products);
        }  else if (action.equalsIgnoreCase("3x_list")){
        	int producttype = Integer.parseInt(request.getParameter("producttype"));
        	forward = TYPE_3X_LIST;
            List<Product> products = dao.getProductsByType(producttype);
            request.setAttribute("products", products);
        }  else if (action.equalsIgnoreCase("4x_list")){
        	int producttype = Integer.parseInt(request.getParameter("producttype"));
        	forward = TYPE_4X_LIST;
            List<Product> products = dao.getProductsByType(producttype);
            request.setAttribute("products", products);
        } else if("insert".equals(action)){
        	forward = "adminAddProduct.jsp";
        } else {
            forward = MAIN;
        }
        
        RequestDispatcher view = request.getRequestDispatcher(forward);
        view.forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    	request.setCharacterEncoding("UTF-8");
    	response.setContentType("text/html;charset=UTF-8");
    	
    	Product product = new Product();
    	
    	product.setProducttype(Integer.parseInt(request.getParameter("producttype")));
    	product.setProductname(request.getParameter("productname"));
    	product.setImg(request.getParameter("img"));
    	product.setExplanation(request.getParameter("explanation"));
    	product.setPrice(Integer.parseInt(request.getParameter("price")));
    	product.setQty(Integer.parseInt(request.getParameter("qty")));
        
        String productIdx = request.getParameter("productidx");
        if(productIdx == null || productIdx.isEmpty())
        {
            dao.addProduct(product);
        }
        else
        {
        	product.setProductidx(Integer.parseInt(productIdx));
            dao.updateProduct(product);
        }
        RequestDispatcher view = request.getRequestDispatcher(MAIN);
        request.setAttribute("products", dao.getAllProducts());
        view.forward(request, response);
    }
}