set nocompatible              " be iMproved, required
filetype off                  " required
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'gmarik/Vundle.vim'
Bundle 'zah/nimrod.vim'
Plugin 'flazz/vim-colorschemes'
Bundle "pangloss/vim-javascript"
Plugin 'jelera/vim-javascript-syntax'
Plugin 'nathanaelkane/vim-indent-guides'
Bundle 'scrooloose/syntastic'
Bundle 'Valloric/YouCompleteMe'
Bundle 'marijnh/tern_for_vim'
Plugin 'elzr/vim-json'
Bundle 'scrooloose/nerdtree'
Plugin 'wting/rust.vim'
call vundle#end()
filetype plugin indent on    " required

filetype plugin on


set expandtab
set cindent
set shiftwidth=4
set tabstop=4
set number

vnoremap > >gv
vnoremap < <gv

set incsearch
set hlsearch

set t_Co=256
syntax on

set backspace=indent,eol,start

colorscheme distinguished
" set background=dark

let g:indent_guides_auto_colors = 0
autocmd VimEnter,Colorscheme * :hi IndentGuidesOdd  guibg=red   ctermbg=3
autocmd VimEnter,Colorscheme * :hi IndentGuidesEven guibg=green ctermbg=4

let g:ycm_add_preview_to_completeopt=0
let g:ycm_confirm_extra_conf=0
set completeopt-=preview

map <F10> :q!<CR>
imap <F10> <ESC>:q!<CR>

map <F2> :w<CR>
imap <F2> <ESC>:w<CR>
