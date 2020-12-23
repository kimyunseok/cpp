package com.inhamall.model;

public class Product {
	private static final long serialVersionUID = 1L;
	

	private int productidx;
	private int producttype;
	/*
	 * 1x : 컴퓨터 노트북, 2x : PC장치(모니터 키보드 마우스), 3x : PC 주장치, 4x : 게이밍 관련
	 * 
	 * 11 : 노트북 / 12 : 맥(애플) / 13 : 데스크탑 / 14: 태블릿 PC
	 * 21 : 모니터 / 22 : 마우스 / 23 : 키보드 / 24 : 스피커 / 25 : 헤드폰
	 * 31 : CPU / 32 : 램 / 33 : 그래픽카드 / 34 : 하드
	 * 41 : 게이밍 장비 / 42 : 게임 / 43 : 공유기 / 44 : 프린터 / 45 : 기타
	 * */
	private String productname;
	private String img;
	private String explanation;
	private int price;
	private int qty;
	
	public int getProductidx() {
		return productidx;
	}
	public void setProductidx(int productidx) {
		this.productidx = productidx;
	}
	public int getProducttype() {
		return producttype;
	}
	public void setProducttype(int producttype) {
		this.producttype = producttype;
	}
	public String getProductname() {
		return productname;
	}
	public void setProductname(String productname) {
		this.productname = productname;
	}
	public String getImg() {
		return img;
	}
	public void setImg(String img) {
		this.img = img;
	}
	public String getExplanation() {
		return explanation;
	}
	public void setExplanation(String explanation) {
		this.explanation = explanation;
	}
	public int getPrice() {
		return price;
	}
	public void setPrice(int price) {
		this.price = price;
	}
	public int getQty() {
		return qty;
	}
	public void setQty(int qty) {
		this.qty = qty;
	}
	
	@Override
	public String toString() {
		return "Product [productidx=" + productidx + ", producttype=" + producttype + ", productname=" + productname
				+ ", img=" + img + ", explanation=" + explanation + ", price=" + price + ", qty=" + qty + "]";
	}
	
	
}
